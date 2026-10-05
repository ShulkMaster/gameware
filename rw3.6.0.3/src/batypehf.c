#include "gameware/batypehf.h"

void _rwObjectHasFrameSetFrame(void *arg0, RWbaframeUnk00 *arg1)
{
    RWbatypehfUnk00 *owner = arg0;

    if (owner->unk04 != 0) {
        RWbaframeUnk01 *before;

        owner->unk08.unk04->unk00 = owner->unk08.unk00;
        before = owner->unk08.unk04;
        owner->unk08.unk00->unk04 = before;
    }
    ((RWbatypehfUnk00 *)arg0)->unk04 = arg1;
    if (arg1 != 0) {
        RWbaframeUnk01 *link;

        owner->unk08.unk00 = arg1->unk90.unk00;
        owner->unk08.unk04 = &arg1->unk90;
        arg1->unk90.unk00->unk04 = &owner->unk08;
        link = &owner->unk08;
        arg1->unk90.unk00 = link;
        RwFrameUpdateObjects(arg1);
    }
}

void _rwObjectHasFrameReleaseFrame(void *arg0)
{
    RWbatypehfUnk00 *owner = arg0;

    if (owner->unk04 != 0) {
        RWbaframeUnk01 *before;

        owner->unk08.unk04->unk00 = owner->unk08.unk00;
        before = owner->unk08.unk04;
        owner->unk08.unk00->unk04 = before;
    }
}
