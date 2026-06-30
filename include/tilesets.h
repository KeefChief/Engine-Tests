#pragma once

#include "platform.h"

typedef struct Tileset{
    Image tex;
    const char *name;
    int w;
    int h;
}Tileset;

typedef struct TilesetMan{
    Tileset **tilesets;
    int count;
}TilesetMan;

Tileset *LoadTileset(Platform p, const char *path);
