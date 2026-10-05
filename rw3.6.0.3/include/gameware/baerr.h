#ifndef GAMEWARE_BAERR_H
#define GAMEWARE_BAERR_H

typedef struct RWbaerrUnk00 {
    int unk00;
    int unk04;
} RWbaerrUnk00;

typedef struct RWbaerrUnk01 {
    int unk00;
    unsigned int unk04;
} RWbaerrUnk01;

typedef struct RWbaerrUnk02 {
    char unk00;
    char unk01;
    short unk02;
    char *unk04;
    char *unk08;
} RWbaerrUnk02;

enum {
    stkCleared = 0x80000000,
    stkHighBit = 0x80000000
};

void *_rwErrorOpen(void *arg0, int arg1, int arg2);
void *_rwErrorClose(void *arg0, int arg1, int arg2);
void RwErrorSet(RWbaerrUnk01 *arg0);
void RwErrorGet(RWbaerrUnk01 *arg0);
unsigned int _rwerror(unsigned int arg0, ...);

#endif
