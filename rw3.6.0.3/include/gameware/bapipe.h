#ifndef GAMEWARE_BAPIPE_H
#define GAMEWARE_BAPIPE_H

extern int _rxPipelineGlobalsOffset;

void *_rwRenderPipelineOpen(void *arg0, int arg1, int arg2);
void *_rwRenderPipelineClose(void *arg0, int arg1, int arg2);
int _rwPipeAttach(void);
void _rwPipeInitForCamera(void *arg0);

#endif
