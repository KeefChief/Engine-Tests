#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>
#include <stdint.h>
#include <stdlib.h>
#include "platform.h"
#include "commondefines.h"
#include "consts.h"
#include "input.h"
#include "tilesets.h"

struct PlatformBackend{
    SDL_Renderer *ren;
    SDL_Window *win;
    SDL_Event e;
};

struct ImageBackend{
    SDL_Texture *tex;
};

static Key GetKeyFromEvent(SDL_Event e){
    switch(e.key.keysym.sym){
	case SDLK_z: return KEY_UP;
	case SDLK_s: return KEY_DOWN;
	case SDLK_q: return KEY_LEFT;
	case SDLK_d: return KEY_RIGHT;
	case SDLK_SPACE: return KEY_JUMP;
    }
    return KEY_UNKNOWN;
}

Platform InitPlatform(){
    Platform p = {0};
    p.frame_start = SDL_GetPerformanceCounter();
    p.perf_freq =SDL_GetPerformanceFrequency();
    p.running = 1;
    p.gameRect = (Rect){0, 0, SCREENW, SCREENH};
    p.backend = malloc(sizeof(*p.backend));
    SDL_Init(SDL_INIT_VIDEO);
    p.backend->win = SDL_CreateWindow(NAME, 0, 0, SCREENW, SCREENH, SDL_WINDOW_RESIZABLE);
    p.backend->ren = SDL_CreateRenderer(p.backend->win, -1, 0);
    SDL_RenderSetLogicalSize(p.backend->ren, SCREENW, SCREENH);
    return p;
}

void ConsumeInput(Platform *p){
    UpdateInput();
    while(SDL_PollEvent(&p->backend->e)){
	switch(p->backend->e.type){
	    case SDL_QUIT:
		p->running = 0;
		break;
	    case SDL_KEYDOWN:
		SetKeyDown(GetKeyFromEvent(p->backend->e));
		break;
	    case SDL_KEYUP:
		SetKeyUp(GetKeyFromEvent(p->backend->e));
		break;
	}
    }
}

Image LoadImage(Platform p, const char *path){
    Image img = {0};
    img.backend = malloc(sizeof(*img.backend));
    printf("path: %s\n", path);
    SDL_Surface *surf = IMG_Load(path);
    if(!surf){
	printf("Could not create image from path: %s\n", path);
	img.backend->tex = NULL;
	return img;
    }
    img.backend->tex = SDL_CreateTextureFromSurface(p.backend->ren, surf);
    return img;
}

void PutSrpite(Platform p, Image img, Rect src, Rect dst){
    if(!img.backend->tex){
	printf("The image wasn't loaded properly and doesnt have a Texture\n");
	return;
    }
    SDL_Rect dstrect = {dst.x, dst.y, dst.w, dst.h};
    SDL_Rect srcrect = {src.x, src.y, src.w, src.h};
    SDL_RenderCopy(p.backend->ren, img.backend->tex, &srcrect, &dstrect);
}

void GetImageSize(int *w, int *h, Image img){
    SDL_QueryTexture(img.backend->tex, NULL, NULL, w, h);
}

void PresentPlatform(Platform p){
    SDL_RenderPresent(p.backend->ren);
    SDL_SetRenderDrawColor(p.backend->ren, 28, 28, 48, 0);
    SDL_RenderClear(p.backend->ren);
    SDL_SetRenderDrawColor(p.backend->ren, 0, 0, 0, 0);
    SDL_Rect gameRect = (SDL_Rect){p.gameRect.x, p.gameRect.y, p.gameRect.w, p.gameRect.h};
    SDL_RenderFillRect(p.backend->ren, &gameRect);
}

Image CreateBatch(Platform p, unsigned char *data, const char* tileset_path, int tile_size, int w, int h){
    Tileset *tileset = GetTilesetFromPath(p, tileset_path); 
    SDL_Rect dstrect = {0, 0, tile_size, tile_size};
    SDL_Rect srcrect = {0, 0, tile_size, tile_size};
    SDL_Texture *tex = SDL_CreateTexture(p.backend->ren, 
	    SDL_PIXELFORMAT_RGBA8888, 
	    SDL_TEXTUREACCESS_TARGET, 
	    w * tile_size, 
	    h * tile_size);
    SDL_SetRenderTarget(p.backend->ren, tex);
    for(int y = 0; y < h; y++){
	for(int x = 0; x < w; x++){
	    dstrect.x = x * tile_size;
	    dstrect.y = y * tile_size;
	    unsigned char cur = data[(y * w) + x];
	    srcrect.x = (cur % tileset->w) * tile_size;
	    srcrect.y = (cur / tileset->w) * tile_size;
	    printf("Src X: %d Src Y: %d\n", srcrect.x, srcrect.y);  
	    SDL_RenderCopy(p.backend->ren, tileset->img.backend->tex, &srcrect, &dstrect);
	}
    }
    SDL_SetRenderTarget(p.backend->ren, NULL);
    Image batch;
    batch.backend = malloc(sizeof(*batch.backend));
    batch.backend->tex = tex;
    return batch;
}

void LimitFramerate(Platform *p){
    Uint64 frame_end = SDL_GetPerformanceCounter();
    double elapsed = (double)(frame_end - p->frame_start) / p->perf_freq;
    double target = 1.0 / TARGET_FPS;
    if(elapsed < target){
	SDL_Delay((Uint32)((target - elapsed) * 1000.0));
    }
    frame_end = SDL_GetPerformanceCounter();
    p->frame_start = SDL_GetPerformanceCounter();
}

void QuitPlatform(Platform p){
    printf("%p\n", p.backend->ren);
    SDL_DestroyRenderer(p.backend->ren);
    printf("Renderer Destroyed\n");
    SDL_DestroyWindow(p.backend->win);
    printf("Window Destroyed\n");
    free(p.backend);
    printf("Backend Destroyed\n");
    SDL_Quit();
    printf("SDL Quit\n");
}
