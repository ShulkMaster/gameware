#include "gameware/rwgrp.h"
#include "gameware/badevice.h"

static unsigned int _rwChunkGroupFListBlockSize = 16;
static unsigned int _rwChunkGroupFListPreallocBlocks = 1;
static RWbamemoryUnk00 _rwChunkGroupFList;
static RWrwgrpUnk00 chunkGroupModule;

void *_rwChunkGroupOpen(void *arg0, int arg1, int arg2)
{
    chunkGroupModule.unk00 = arg1;
    *(RWbamemoryUnk00 **)&RwEngineInstance[chunkGroupModule.unk00] =
        RwFreeListCreateAndPreallocateSpace(33, _rwChunkGroupFListBlockSize, 4, _rwChunkGroupFListPreallocBlocks,
                                            &_rwChunkGroupFList, 0x40412);
    if (*(RWbamemoryUnk00 **)&RwEngineInstance[chunkGroupModule.unk00] == 0) {
        return 0;
    }
    chunkGroupModule.unk04 += 1;
    return arg0;
}

void *_rwChunkGroupClose(void *arg0, int arg1, int arg2)
{
    if (*(RWbamemoryUnk00 **)&RwEngineInstance[chunkGroupModule.unk00] != 0) {
        RwFreeListDestroy(*(RWbamemoryUnk00 **)&RwEngineInstance[chunkGroupModule.unk00]);
    }
    chunkGroupModule.unk04 -= 1;
    return arg0;
}
