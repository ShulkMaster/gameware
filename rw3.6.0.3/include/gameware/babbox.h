#ifndef GAMEWARE_BABBOX_H
#define GAMEWARE_BABBOX_H

typedef struct RWbabboxUnk01 {
    float unk00;
    float unk04;
    float unk08;
} RWbabboxUnk01;

typedef struct RWbabboxUnk00 {
    RWbabboxUnk01 unk00;
    RWbabboxUnk01 unk0C;
} RWbabboxUnk00;

void RwBBoxCalculate(RWbabboxUnk00 *arg0, RWbabboxUnk01 *arg1, int arg2);

#endif
