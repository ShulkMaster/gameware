#ifndef GAMEWARE_BAFRAME_H
#define GAMEWARE_BAFRAME_H

typedef struct RWbaframeUnk01 {
    struct RWbaframeUnk01 *unk00;
    struct RWbaframeUnk01 *unk04;
} RWbaframeUnk01;

typedef struct RWbaframeUnk00 {
    unsigned char unk00[0x90];
    RWbaframeUnk01 unk90;
} RWbaframeUnk00;

void RwFrameUpdateObjects(RWbaframeUnk00 *arg0);

#endif
