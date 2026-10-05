#include "gameware/bapipe.h"
#include "gameware/p2core.h"

/* Provenance: GLOBAL OBJECT MKD ELF #23481 .sbss 0x80511640 size 4 */
int _rxPipelineGlobalsOffset;

void *_rwRenderPipelineOpen(void *arg0, int arg1, int arg2)
{
    _rxPipelineGlobalsOffset = arg1;
    if (_rxPipelineOpen() == 0) {
        return 0;
    }
    return arg0;
}

void *_rwRenderPipelineClose(void *arg0, int arg1, int arg2)
{
    _rxPipelineClose();
    return arg0;
}

int _rwPipeAttach(void)
{
    return 1;
}

void _rwPipeInitForCamera(void *arg0)
{
}
