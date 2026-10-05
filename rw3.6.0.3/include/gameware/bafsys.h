#ifndef GAMEWARE_BAFSYS_H
#define GAMEWARE_BAFSYS_H

#include "runtime/cfile.h"

typedef int (*RWCBRwfexist)(char *);
typedef FILE *(*RWCBFopen)(const char *, const char *);
typedef int (*RWCBFclose)(FILE *);
typedef size_t (*RWCBFread)(void *, size_t, size_t, FILE *);
typedef size_t (*RWCBFwrite)(const void *, size_t, size_t, FILE *);
typedef char *(*RWCBFgets)(char *, int, FILE *);
typedef int (*RWCBFputs)(const char *, FILE *);
typedef int (*RWCBFeof)(FILE *);
typedef int (*RWCBFseek)(FILE *, u32, int);
typedef int (*RWCBFflush)(FILE *);
typedef long (*RWCBFtell)(FILE *);

typedef struct RWbafsysUnk00 {
    RWCBRwfexist unk00;
    RWCBFopen unk04;
    RWCBFclose unk08;
    RWCBFread unk0C;
    RWCBFwrite unk10;
    RWCBFgets unk14;
    RWCBFputs unk18;
    RWCBFeof unk1C;
    RWCBFseek unk20;
    RWCBFflush unk24;
    RWCBFtell unk28;
} RWbafsysUnk00;

enum {
    stkFileTable = 0xC4
};

RWbafsysUnk00 *RwOsGetFileInterface(void);
int _rwFileSystemOpen(void);
void _rwFileSystemClose(void);

#endif
