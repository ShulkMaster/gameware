#include "gameware/bacolor.h"

static RWbacolorUnk00 colorModule;

void *_rwColorOpen(void *arg0, int arg1, int arg2)
{
    colorModule.unk04++;
    return arg0;
}

void *_rwColorClose(void *arg0, int arg1, int arg2)
{
    colorModule.unk04--;
    return arg0;
}
