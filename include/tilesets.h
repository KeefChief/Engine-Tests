#pragma once

#include "platform.h"

typedef struct Tileset{
    Image img;
    const char *name;
    const char *path;
    int w;
    int h;
}Tileset;

typedef struct TilesetMan{
    Tileset **tilesets;
    int count;
}TilesetMan;

Tileset *LoadTileset(Platform p, const char *path);
Tileset *GetTilesetFromPath(Platform p, const char *path);
