#ifndef GAMEWARE_BAMEMORY_H
#define GAMEWARE_BAMEMORY_H

typedef struct RWbamemoryUnk00 {
    unsigned char unk00[0x24];
} RWbamemoryUnk00;

RWbamemoryUnk00 *RwFreeListCreateAndPreallocateSpace(unsigned int arg0, unsigned int arg1, unsigned int arg2,
                                                     unsigned int arg3, RWbamemoryUnk00 *arg4, unsigned int arg5);
int RwFreeListDestroy(RWbamemoryUnk00 *arg0);

#endif
