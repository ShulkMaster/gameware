#include "gameware/basector.h"

RWbatkregUnk00 sectorTKList = {0x88, 0x88};
static RWbasectorUnk00 sectorModule;

void *_rpSectorOpen(void *arg0, int arg1, int arg2)
{
    sectorModule.unk04 += 1;
    return arg0;
}

void *_rpSectorClose(void *arg0, int arg1, int arg2)
{
    sectorModule.unk04 -= 1;
    return arg0;
}

int RpWorldSectorRegisterPlugin(int arg0, int arg1, RWCBPluginDefaultConstructor arg2, RWCBPluginDefaultDestructor arg3,
                                RWCBPluginDefaultCopy arg4)
{
    int offset = _rwPluginRegistryAddPlugin(&sectorTKList, arg0, arg1, arg2, arg3, arg4);

    return offset;
}

int RpWorldSectorRegisterPluginStream(int arg0, RWCBStreamRead arg1, RWCBStreamWrite arg2, RWCBStreamSize arg3)
{
    return 0;
}
