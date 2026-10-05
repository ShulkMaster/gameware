#include "gameware/baerr.h"
#include "gameware/badevice.h"

static RWbaerrUnk00 errorModule;

void *_rwErrorOpen(void *arg0, int arg1, int arg2)
{
    errorModule.unk00 = arg1;
    errorModule.unk04 += 1;
    ((RWbaerrUnk01 *)&RwEngineInstance[errorModule.unk00])->unk00 = 0;
    ((RWbaerrUnk01 *)&RwEngineInstance[errorModule.unk00])->unk04 = stkCleared;
    return arg0;
}

void *_rwErrorClose(void *arg0, int arg1, int arg2)
{
    errorModule.unk04 -= 1;
    return arg0;
}

void RwErrorSet(RWbaerrUnk01 *arg0)
{
    if (((RWbaerrUnk01 *)&RwEngineInstance[errorModule.unk00])->unk00 == 0) {
        if (((RWbaerrUnk01 *)&RwEngineInstance[errorModule.unk00])->unk04 == stkCleared) {
            if (arg0->unk04 & stkHighBit) {
                ((RWbaerrUnk01 *)&RwEngineInstance[errorModule.unk00])->unk00 = 0;
            } else {
                ((RWbaerrUnk01 *)&RwEngineInstance[errorModule.unk00])->unk00 = arg0->unk00;
            }
            ((RWbaerrUnk01 *)&RwEngineInstance[errorModule.unk00])->unk04 = arg0->unk04;
        }
    }
}

void RwErrorGet(RWbaerrUnk01 *arg0)
{
    *arg0 = *(RWbaerrUnk01 *)&RwEngineInstance[errorModule.unk00];
    ((RWbaerrUnk01 *)&RwEngineInstance[errorModule.unk00])->unk00 = 0;
    ((RWbaerrUnk01 *)&RwEngineInstance[errorModule.unk00])->unk04 = stkCleared;
}

unsigned int _rwerror(unsigned int arg0, ...)
{
    RWbaerrUnk02 args;

    __builtin_va_info(&args);
    return arg0;
}
