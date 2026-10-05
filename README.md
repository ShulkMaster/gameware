# gameware

Reconstruction of the RenderWare Graphics libraries that the Midway GameCube
*Mortal Kombat* titles link statically. Every source line is derived from
retail evidence: shipped binaries, their symbol tables, and cross-platform
builds of the same game. Leaked RenderWare source and SDK headers are not
sources.

## Versions

The GC versions were verified from the retail `RwEngineGetVersion`, which
returns a constant. The PS2 build inlines the getter, so its version comes
from the stream-version range checks, which accept `0x34000 <= v < 0x36004`.

| Dir | Game | Retail code | Version | Evidence |
| --- | --- | --- | --- | --- |
| `rw3.2.0.0/` | MK: Deadly Alliance (GC, `GMKE5D`) | `lis r3,3; addi r3,r3,0x2000` → `0x32000` | 3.2.0.0 | `mk5gc_release.elf` @ `0x801BBABC` |
| `rw3.6.0.3/` | MK: Deception (GC, `GQNE5D`) | `lis r3,3; addi r3,r3,0x6003` → `0x36003` | 3.6.0.3 | `mk6gc_release.elf` @ `0x80256ADC` |
| — | MK: Deception (PS2, `SLUS_208.81`) | `lui at,3; ori at,at,0x6004; sltu at,v0,at` → `v < 0x36004` | 3.6.0.3 | `SLUS_208.81` @ `0x001A7BA0` |

## Evidence sources

This repository does not contain any game assets.

| Source | File | SHA-1 | Gives |
| --- | --- | --- | --- |
| MKDA GC ELF | `mk5gc_release.elf` | `5344a885…` | Symbols, code, relocations |
| MKDA GC DOL | `main.dol` | `3560bd0c…` | Final retail image |
| MKD GC ELF | `mk6gc_release.elf` | `bb3a64e8…` | Symbols, code, relocations |
| MKD GC MAP | `mk6gc_release.MAP` | `a653ad48…` | Object/library layout (`rwcore.a/baframe.obj` …) |
| MKD GC DOL | `main.dol` | `ef001212…` | Final retail image |
| MKD PS2 ELF | `SLUS_208.81` | `7657eff0…` | Cross-platform shape: non-inlined helpers, constants, case order |

## Libraries in scope

From the Deception MAP and the host split configurations:

| Library | MKD 3.6.0.3 units | MKDA 3.2.0.0 |
| --- | --- | --- |
| `rwcore.a` | 50 | flattened into `renderware/` (50 units, all libraries) |
| `rpworld.a` | 31 | ″ |
| `rpskin.a` | 9 | ″ |
| `rpmatfx.a` | 8 | ″ |
| `rphanim.a` | 2 | ″ |
| `rpspecular.a`, `rtanim.a`, `rtquat.a` | 1 each | ″ |
| `rptoon.a`, `rpskintoon.a`, `rpskinmatfx.a`, `rpskinmatfxtoon.a` | in MAP, not yet split | n/a |

## Layout

```
gameware/
  rw3.2.0.0/       MKDA RenderWare (GMKE5D)
  rw3.6.0.3/       MKD RenderWare (GQNE5D)
  tools/           host build check
```

Each version tree contains:

```
rwX/
  src/                units, named like the host game's RenderWare units
  include/gameware/   headers, included as "gameware/<name>.h"
```

## Tools

Host decomps use this repository as the `extern/gameware` submodule. Each
host decides which units it builds and links.

`tools/check_rw.py` places a gameware checkout at a host's
`extern/gameware` path and:

1. Builds the host unchanged, including its retail SHA-1 check, so every
   unit the host links must still match.
2. Reports code and data match per unit and whether the host links it. With
   `--baseline` it also builds a second gameware checkout and marks each unit
   as new, improved, or regressed.
