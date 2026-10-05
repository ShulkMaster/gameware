#ifndef GAMEWARE_BATKREG_H
#define GAMEWARE_BATKREG_H

typedef void *(*RWCBPluginDefaultConstructor)(void *, int, int);
typedef void *(*RWCBPluginDefaultDestructor)(void *, int, int);
typedef void *(*RWCBPluginDefaultCopy)(void *, void *, int, int);
typedef void *(*RWCBStreamRead)(void *, int, void *, int, int);
typedef void *(*RWCBStreamWrite)(void *, int, void *, int, int);
typedef int (*RWCBStreamSize)(void *, int, int);

typedef struct RWbatkregUnk00 {
    int unk00;
    int unk04;
    int unk08;
    int unk0C;
    struct RWbatkregUnk01 *unk10;
    struct RWbatkregUnk01 *unk14;
} RWbatkregUnk00;

int _rwPluginRegistryAddPlugin(RWbatkregUnk00 *arg0, int arg1, int arg2, RWCBPluginDefaultConstructor arg3,
                               RWCBPluginDefaultDestructor arg4, RWCBPluginDefaultCopy arg5);

#endif
