#include "tilesets.h"
#include "consts.h"
#include "platform.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static TilesetMan tileset_man = {0};

Tileset *LoadTileset(Platform p, const char *path){
    tileset_man.tilesets = realloc(tileset_man.tilesets, (tileset_man.count + 1) * sizeof(Tileset*));
    tileset_man.tilesets[tileset_man.count] = malloc(sizeof(Tileset));
    Tileset *tileset = tileset_man.tilesets[tileset_man.count++];
    tileset->img = LoadImage(p, path);
    const char *name = strrchr(path, '/') + 1;
    const char *dot = strrchr(path, '.');
    size_t size = (size_t)(dot - name);
    char *out = malloc(size + 1);
    memcpy(out, name, size);
    out[size] = '\0';
    printf("Tileset name: %s\n", out);
    tileset->name = out;
    tileset->path = path;
    int w, h;
    GetImageSize(&w, &h, tileset->img);
    tileset->w = w / TILE_SIZE;
    tileset->h = h / TILE_SIZE;
    return tileset;
}

Tileset *GetTilesetFromPath(Platform p, const char *path){
    for(int i = 0; i < tileset_man.count; i++){
	if(strcmp(path, tileset_man.tilesets[i]->path) == 0){
	    return tileset_man.tilesets[i];
	}
    }
    return LoadTileset(p, path);
}
