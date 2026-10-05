#include "gameware/babbox.h"

void RwBBoxCalculate(RWbabboxUnk00 *arg0, RWbabboxUnk01 *arg1, int arg2)
{
    arg0->unk0C = arg1[0];
    arg0->unk00 = arg1[0];

    for (arg1 += 1, arg2 -= 1; arg2-- != 0; arg1++) {
        if (arg0->unk0C.unk00 > arg1->unk00) {
            arg0->unk0C.unk00 = arg1->unk00;
        }
        if (arg0->unk0C.unk04 > arg1->unk04) {
            arg0->unk0C.unk04 = arg1->unk04;
        }
        if (arg0->unk0C.unk08 > arg1->unk08) {
            arg0->unk0C.unk08 = arg1->unk08;
        }
        if (arg0->unk00.unk00 < arg1->unk00) {
            arg0->unk00.unk00 = arg1->unk00;
        }
        if (arg0->unk00.unk04 < arg1->unk04) {
            arg0->unk00.unk04 = arg1->unk04;
        }
        if (arg0->unk00.unk08 < arg1->unk08) {
            arg0->unk00.unk08 = arg1->unk08;
        }
    }
}
