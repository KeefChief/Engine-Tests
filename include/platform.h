#pragma once
#include "commondefines.h"

typedef struct ImageBackend ImageBackend;
typedef struct PlatformBackend PlatformBackend;

typedef struct Platform {
    int running;
    Rect gameRect;
    PlatformBackend *backend;
}Platform;

typedef struct Image{
    ImageBackend *backend;
}Image;

Platform InitPlatform();
void ConsumeInput(Platform *p);
Image LoadImage(Platform p, const char *path);
void PutSrpite(Platform p, Image img, Rect src, Rect dst);
void PresentPlatform(Platform p);
void QuitPlatform(Platform p);
