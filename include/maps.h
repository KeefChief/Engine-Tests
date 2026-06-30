#pragma once

#include "platform.h"
#include <stdint.h>

typedef struct MapData{
    unsigned char *data;
    int w;
    int h;
}MapData;

typedef struct Map{
    Image batch;
    uint16_t w;
    uint16_t h;
    unsigned char *data;
}Map;

void LoadMap(Platform p, const char *path);
void PutMap(Platform p);
