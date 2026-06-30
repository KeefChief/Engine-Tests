#include "tilesets.h"
#include "platform.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static TilesetMan tileset_man = {0};

Tileset *LoadTileset(Platform p, const char *path){
    tileset_man.tilesets[tileset_man.count] = malloc(sizeof(Tileset));
    Tileset *tileset = tileset_man.tilesets[tileset_man.count++];
    tileset->tex = LoadImage(p, path);
    const char *name = strrchr(path, '/');
    const char *dot = strrchr(path, '.');
    size_t size = (size_t)(dot - name);
    char *out = malloc(size);
    memcpy(out, name, size);
    printf("Tileset name: %s\n", out);
    tileset->name = out;
    return tileset;
}

Tileset *GetTileset(const char *name){

}
