#include "maps.h"
#include "consts.h"
#include "platform.h"
#include "tilesets.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Map current_map = {0};

static char *ExtractPath(FILE *f){
    char buf[32];
    int buf_count = 0;
    if(fgetc(f) != ':'){
	printf("From ExtractPath: Forgot ':' after TYPE in mph file\n");
    }
    while((buf[buf_count] = fgetc(f)) != '\n' && buf_count < 32){
	buf_count++;
    }
    char *path = malloc(buf_count + 1);
    memcpy(path, buf, buf_count);
    path[buf_count] = '\0';
    return path;
}

static int GetDataFromMap(const char* path){
    FILE *map = fopen(path, "rb");
    if(!map){
	printf("From GetDataFromMap: Map path is wrong\n");
	return 0;
    }
    char magic[4] = "";
    fread(magic, 1, 3, map);
    fread(&current_map.w, 2, 1, map);
    fread(&current_map.h, 2, 1, map);
    printf("From GetDataFromMap:\n\twidth: %d\n\theight: %d\n", current_map.w, current_map.h);
    int size = current_map.w * current_map.h;
    free(current_map.data);
    current_map.data = malloc(size);
    fread(current_map.data, 1, size, map);
    printf("Current data at index 0: %d\n", current_map.data[0]);
    fclose(map);
    return 1;
}

void LoadMap(Platform p, const char *path){
    FILE *map_handle = fopen(path, "rb");
    char *map_path;
    char *set_path;
    char c;
    char cur_type[4] = "";
    int count = 0;
    while((c = fgetc(map_handle)) != EOF){
	cur_type[count] = c;
	count = (count + 1) % 3;
	printf("Count: %d\n", count);
	printf("Cur type: %s\n", cur_type);
	if(strcmp(cur_type, "MAP") == 0){
	    count = 0;
	    map_path = ExtractPath(map_handle);
	    printf("Map path: %s\n", map_path);
	}
	else if(strcmp(cur_type, "SET") == 0){
	    count = 0;
	    set_path = ExtractPath(map_handle);
	}
    }
    if(!map_path || !set_path){
	printf("From LoadMap: Could not find map or tileset path\n");
	return;
    }
    if(GetDataFromMap(map_path)){
	current_map.batch = CreateBatch(p, current_map.data, set_path, TILE_SIZE, current_map.w, current_map.h);
    }
    fclose(map_handle);
}

void PutMap(Platform p){
    Rect src = {0, 0, current_map.w * TILE_SIZE, current_map.h * TILE_SIZE};
    Rect dst = {0, 0, current_map.w * TILE_SIZE, current_map.h * TILE_SIZE};
    PutSrpite(p, current_map.batch, src, dst);
}
