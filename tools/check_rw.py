#!/usr/bin/env python3
"""Check a gameware commit inside a host decomp that uses it as a submodule.

The host decides which gameware units it builds and links. This tool swaps
the gameware commit under test into the host's submodule path, builds the
host unchanged with its retail SHA-1 check, and reports per-unit matches.
"""

import argparse
import json
import re
import shutil
import struct
import subprocess
import sys
from pathlib import Path

SUBMODULE = "extern/gameware"

# Host RenderWare headers per game version: the poisoned tree.
POISONED_INCLUDES = {
    "GMKE5D": ["include/renderware"],
    "GQNE5D": ["include/rw"],
}

DEFINE_RE = re.compile(r"^\s*#\s*define\s+(\w+)(.*)$")
IFNDEF_RE = re.compile(r"^\s*#\s*ifndef\s+(\w+)\s*$")
SUBMODULE_RE = re.compile(r"^\s*path\s*=\s*(\S+)\s*$", re.MULTILINE)

IMAGE_TOOLS = [
    "--binutils", "/binutils", "--compilers", "/compilers",
    "--dtk", "/tools/dtk", "--objdiff", "/tools/objdiff-cli",
    "--wrapper", "/tools/wibo", "--sjiswrap", "/tools/sjiswrap.exe",
]


def fail(message: str) -> None:
    print(f"error: {message}", file=sys.stderr)
    sys.exit(1)


def sources(gameware: Path) -> list:
    return sorted(
        p
        for tree in gameware.glob("rw*")
        for p in tree.rglob("*")
        if p.suffix in (".c", ".h")
    )


def check_macros(gameware: Path) -> list:
    """Allow only `#ifndef X` + `#define X` include guards."""
    errors = []
    for path in sources(gameware):
        previous = ""
        for number, line in enumerate(path.read_text().splitlines(), 1):
            define = DEFINE_RE.match(line)
            if define:
                guard = IFNDEF_RE.match(previous)
                is_guard = (
                    guard is not None
                    and guard.group(1) == define.group(1)
                    and define.group(2).strip() == ""
                )
                if not is_guard:
                    rel = path.relative_to(gameware)
                    errors.append(f"{rel}:{number}: macro `{define.group(1)}`")
            if line.strip():
                previous = line
    return errors


def uses_gameware(host: Path) -> bool:
    gitmodules = host / ".gitmodules"
    if not gitmodules.exists():
        return False
    return SUBMODULE in SUBMODULE_RE.findall(gitmodules.read_text())


def swap_in(gameware: Path, host: Path) -> None:
    """Replace the host's submodule checkout with the gameware under test.
    Plain copies give fresh mtimes, so no stale object is reused."""
    dest = host / SUBMODULE
    shutil.rmtree(dest, ignore_errors=True)
    shutil.copytree(
        gameware, dest,
        ignore=shutil.ignore_patterns(".git", "__pycache__"),
        copy_function=shutil.copy,
    )


def build(host: Path, version: str, link: bool) -> None:
    shutil.copytree("/orig", host / "orig", dirs_exist_ok=True)
    subprocess.run(
        [sys.executable, "configure.py", "--version", version, *IMAGE_TOOLS],
        cwd=host, check=True,
    )
    targets = ["all_source", f"build/{version}/report.json"]
    if link:
        targets[1:1] = [f"build/{version}/ok", "progress"]
    if subprocess.run(["ninja", *targets], cwd=host).returncode != 0:
        fail(
            f"{host.name}: build failed. If main.dol failed its SHA-1 check, "
            "a unit the host links no longer matches."
        )


def read_deps_log(host: Path) -> dict:
    """Parse the ninja v4 deps log (also written by samurai, the image's
    ninja, which has no `-t deps`). Returns output path -> input paths."""
    data = (host / ".ninja_deps").read_bytes()
    header = b"# ninjadeps\n"
    if not data.startswith(header):
        fail(".ninja_deps: unknown format")
    version = struct.unpack_from("<I", data, len(header))[0]
    if version != 4:
        fail(f".ninja_deps: unsupported version {version}")
    paths = []
    deps = {}
    offset = len(header) + 4
    while offset < len(data):
        head = struct.unpack_from("<I", data, offset)[0]
        size = head & 0x7FFFFFFF
        record = data[offset + 4 : offset + 4 + size]
        offset += 4 + size
        if head & 0x80000000:
            out_id = struct.unpack_from("<I", record, 0)[0]
            # Skip the 64-bit mtime; the rest are input path ids.
            ids = struct.unpack_from(f"<{(size - 12) // 4}I", record, 12)
            deps[paths[out_id]] = [paths[i] for i in ids]
        else:
            paths.append(record[:-4].rstrip(b"\0").decode())
    return deps


def gameware_objects(host: Path) -> dict:
    """Source path -> built object for every unit built from the submodule."""
    objdiff = json.loads((host / "objdiff.json").read_text())
    objects = {}
    for unit in objdiff["units"]:
        source = unit.get("metadata", {}).get("source_path", "")
        if source.startswith(SUBMODULE + "/") and unit.get("base_path"):
            objects[source] = unit["base_path"]
    return objects


def check_includes(host: Path, version: str) -> list:
    """Fail when a unit's recorded dependencies reach a poisoned header."""
    errors = []
    deps = read_deps_log(host)
    poisoned = [(host / p).resolve() for p in POISONED_INCLUDES[version]]
    for source, obj in gameware_objects(host).items():
        if obj not in deps:
            errors.append(f"{source}: no dependency record for {obj}")
            continue
        for dep in deps[obj]:
            path = (host / dep).resolve()
            if any(path.is_relative_to(p) for p in poisoned):
                errors.append(f"{source}: includes poisoned header {dep}")
    return errors


def measure(value: dict, total: str, percent: str) -> float:
    # objdiff omits zero fields; an empty section counts as matched.
    if not int(value.get(total, 0)):
        return 100.0
    return float(value.get(percent, 0.0))


def unit_scores(host: Path, version: str) -> dict:
    """Source path -> (linked, code %, data %) for every gameware unit."""
    report = json.loads((host / "build" / version / "report.json").read_text())
    scores = {}
    for unit in report["units"]:
        meta = unit.get("metadata", {})
        source = meta.get("source_path", "")
        if not source.startswith(SUBMODULE + "/"):
            continue
        measures = unit.get("measures", {})
        scores[source] = (
            bool(meta.get("complete")),
            measure(measures, "total_code", "matched_code_percent"),
            measure(measures, "total_data", "matched_data_percent"),
        )
    return scores


def summarize(scores: dict, base: dict) -> tuple:
    """Markdown table of every unit, and warnings for regressed units."""
    lines = [
        "| Unit | Linked | Code % | Data % | Change |",
        "| --- | --- | ---: | ---: | --- |",
    ]
    warnings = []
    for source in sorted(set(scores) | set(base)):
        name = source.removeprefix(SUBMODULE + "/")
        if source not in scores:
            lines.append(f"| `{name}` | | | | removed |")
            continue
        linked, code, data = scores[source]
        change = ""
        if base:
            if source not in base:
                change = "new"
            else:
                _, base_code, base_data = base[source]
                was = f"{base_code:.2f} / {base_data:.2f}"
                if code < base_code or data < base_data:
                    change = f"regressed from {was}"
                    warnings.append(f"{name}: {change}")
                elif (code, data) != (base_code, base_data):
                    change = f"improved from {was}"
        lines.append(
            f"| `{name}` | {'yes' if linked else 'no'} | {code:.2f} | {data:.2f} | {change} |"
        )
    return lines, warnings


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    parser.add_argument("gameware", type=Path, help="gameware checkout under test")
    parser.add_argument("host", type=Path, help="host decomp checkout")
    parser.add_argument("version", choices=sorted(POISONED_INCLUDES))
    parser.add_argument("--baseline", type=Path, help="baseline gameware checkout")
    parser.add_argument("--summary", type=Path, help="append a Markdown summary")
    args = parser.parse_args()

    gameware = args.gameware.resolve()
    host = args.host.resolve()

    errors = check_macros(gameware)
    if errors:
        fail("macro ban:\n  " + "\n  ".join(errors))

    if not uses_gameware(host):
        message = f"{host.name} has no {SUBMODULE} submodule yet; host check skipped"
        print(f"::warning::{message}")
        if args.summary:
            with args.summary.open("a") as summary:
                summary.write(f"**{args.version}:** {message}.\n\n")
        return

    base_host = None
    if args.baseline:
        base_host = host.with_name(host.name + "-base")
        shutil.rmtree(base_host, ignore_errors=True)
        shutil.copytree(host, base_host, symlinks=True)

    swap_in(gameware, host)
    build(host, args.version, link=True)
    errors = check_includes(host, args.version)
    if errors:
        fail("\n  " + "\n  ".join(errors))
    scores = unit_scores(host, args.version)

    base = {}
    if base_host is not None:
        swap_in(args.baseline.resolve(), base_host)
        # The baseline only provides scores; its link is not judged.
        build(base_host, args.version, link=False)
        base = unit_scores(base_host, args.version)

    lines, warnings = summarize(scores, base)
    print("\n".join(lines))
    for warning in warnings:
        print(f"::warning::{warning}")
    if args.summary:
        with args.summary.open("a") as summary:
            summary.write(f"### {args.version}\n\n" + "\n".join(lines) + "\n\n")
    print(f"{args.version}: OK")


if __name__ == "__main__":
    main()
