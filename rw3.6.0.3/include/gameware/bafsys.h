#ifndef GAMEWARE_BAFSYS_H
#define GAMEWARE_BAFSYS_H

#include "runtime/cfile.h"

typedef struct RWbafsysUnk00 {
    int (*unk00)(char *);
    FILE *(*unk04)(const char *, const char *);
    int (*unk08)(FILE *);
    size_t (*unk0C)(void *, size_t, size_t, FILE *);
    size_t (*unk10)(const void *, size_t, size_t, FILE *);
    char *(*unk14)(char *, int, FILE *);
    int (*unk18)(const char *, FILE *);
    int (*unk1C)(FILE *);
    int (*unk20)(FILE *, u32, int);
    int (*unk24)(FILE *);
    long (*unk28)(FILE *);
} RWbafsysUnk00;

enum {
    stkFileTable = 0xC4
};

RWbafsysUnk00 *RwOsGetFileInterface(void);
int _rwFileSystemOpen(void);
void _rwFileSystemClose(void);

#endif
