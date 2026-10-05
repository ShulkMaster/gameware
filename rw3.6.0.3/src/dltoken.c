#include "gameware/dltoken.h"
#include "dolphin/gx.h"

unsigned short _RwDlTokenCurrent = 1;
unsigned short _RwDlTokenLastSeen;

int _rwDlTokenQueryDone(unsigned short arg0)
{
    int reached;
    int reachedAfterWrap;

    _RwDlTokenLastSeen = GXReadDrawSync();
    if (_RwDlTokenLastSeen >= stkTokenLimit) {
        return 0;
    }
    if (_RwDlTokenCurrent >= _RwDlTokenLastSeen) {
        reached = 1;
        if (arg0 > _RwDlTokenLastSeen) {
            if (arg0 <= _RwDlTokenCurrent) {
                reached = 0;
            }
        }
        return reached;
    }
    reachedAfterWrap = 0;
    if (arg0 > _RwDlTokenCurrent) {
        if (arg0 <= _RwDlTokenLastSeen) {
            reachedAfterWrap = 1;
        }
    }
    return reachedAfterWrap;
}
