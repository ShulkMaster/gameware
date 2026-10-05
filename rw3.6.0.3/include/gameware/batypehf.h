#ifndef GAMEWARE_BATYPEHF_H
#define GAMEWARE_BATYPEHF_H

#include "gameware/baframe.h"

typedef struct RWbatypehfUnk00 {
    unsigned char unk00[4];
    RWbaframeUnk00 *unk04;
    RWbaframeUnk01 unk08;
} RWbatypehfUnk00;

void _rwObjectHasFrameSetFrame(void *arg0, RWbaframeUnk00 *arg1);
void _rwObjectHasFrameReleaseFrame(void *arg0);

#endif
