#include "gameware/bafsys.h"
#include "gameware/badevice.h"

RWbafsysUnk00 *RwOsGetFileInterface(void)
{
    return (RWbafsysUnk00 *)&RwEngineInstance[stkFileTable];
}

static int rwfexist(char *arg0)
{
    FILE *file = ((RWbafsysUnk00 *)&RwEngineInstance[stkFileTable])->unk04(arg0, "rb");
    int found = file != 0;

    if (file != 0) {
        ((RWbafsysUnk00 *)&RwEngineInstance[stkFileTable])->unk08(file);
    }
    return found;
}

int _rwFileSystemOpen(void)
{
    ((RWbafsysUnk00 *)&RwEngineInstance[stkFileTable])->unk00 = rwfexist;
    ((RWbafsysUnk00 *)&RwEngineInstance[stkFileTable])->unk04 = fopen;
    ((RWbafsysUnk00 *)&RwEngineInstance[stkFileTable])->unk08 = fclose;
    ((RWbafsysUnk00 *)&RwEngineInstance[stkFileTable])->unk0C = fread;
    ((RWbafsysUnk00 *)&RwEngineInstance[stkFileTable])->unk10 = fwrite;
    ((RWbafsysUnk00 *)&RwEngineInstance[stkFileTable])->unk14 = fgets;
    ((RWbafsysUnk00 *)&RwEngineInstance[stkFileTable])->unk18 = fputs;
    ((RWbafsysUnk00 *)&RwEngineInstance[stkFileTable])->unk1C = feof;
    ((RWbafsysUnk00 *)&RwEngineInstance[stkFileTable])->unk20 = fseek;
    ((RWbafsysUnk00 *)&RwEngineInstance[stkFileTable])->unk24 = fflush;
    ((RWbafsysUnk00 *)&RwEngineInstance[stkFileTable])->unk28 = ftell;
    return 1;
}

void _rwFileSystemClose(void)
{
}
