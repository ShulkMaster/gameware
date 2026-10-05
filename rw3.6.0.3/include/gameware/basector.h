#ifndef GAMEWARE_BASECTOR_H
#define GAMEWARE_BASECTOR_H

#include "gameware/batkreg.h"

typedef struct RWbasectorUnk00 {
    int unk00;
    int unk04;
} RWbasectorUnk00;

extern RWbatkregUnk00 sectorTKList;

void *_rpSectorOpen(void *arg0, int arg1, int arg2);
void *_rpSectorClose(void *arg0, int arg1, int arg2);
int RpWorldSectorRegisterPlugin(int arg0, int arg1, RWCBPluginDefaultConstructor arg2, RWCBPluginDefaultDestructor arg3,
                                RWCBPluginDefaultCopy arg4);
int RpWorldSectorRegisterPluginStream(int arg0, RWCBStreamRead arg1, RWCBStreamWrite arg2, RWCBStreamSize arg3);

#endif
