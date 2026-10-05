#ifndef GAMEWARE_RWGRP_H
#define GAMEWARE_RWGRP_H

#include "gameware/bamemory.h"

typedef struct RWrwgrpUnk00 {
    int unk00;
    int unk04;
} RWrwgrpUnk00;

void *_rwChunkGroupOpen(void *arg0, int arg1, int arg2);
void *_rwChunkGroupClose(void *arg0, int arg1, int arg2);

#endif
