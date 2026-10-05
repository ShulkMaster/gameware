#ifndef GAMEWARE_DLTOKEN_H
#define GAMEWARE_DLTOKEN_H

enum {
    stkTokenLimit = 0xE000
};

extern unsigned short _RwDlTokenCurrent;
extern unsigned short _RwDlTokenLastSeen;

int _rwDlTokenQueryDone(unsigned short arg0);

#endif
