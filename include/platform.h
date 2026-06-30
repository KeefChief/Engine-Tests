#pragma once
#include "commondefines.h"
#include <stdint.h>

typedef struct ImageBackend ImageBackend;
typedef struct PlatformBackend PlatformBackend;

typedef struct Platform {
    int running;
    Rect gameRect;
    PlatformBackend *backend;
    uint64_t frame_start;
    uint64_t perf_freq;
}Platform;

typedef struct Image{
    ImageBackend *backend;
}Image;

Platform InitPlatform();
void ConsumeInput(Platform *p);
Image LoadImage(Platform p, const char *path);
void PutSrpite(Platform p, Image img, Rect src, Rect dst);
void GetImageSize(int *w, int *h, Image img);
Image CreateBatch(Platform p, unsigned char *data, const char* tileset_path, int tile_size, int w, int h);
void PresentPlatform(Platform p);
void LimitFramerate(Platform p);
void QuitPlatform(Platform p);
