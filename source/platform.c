#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include "platform.h"
#include "commondefines.h"
#include "consts.h"

struct PlatformBackend{
    SDL_Renderer *ren;
    SDL_Window *win;
    SDL_Event e;
};

struct ImageBackend{
    SDL_Texture *tex;
};

Platform InitPlatform(){
    Platform p = {0};
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
    while(SDL_PollEvent(&p->backend->e)){
	switch(p->backend->e.type){
	    case SDL_QUIT:
		p->running = 0;
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

void PresentPlatform(Platform p){
    SDL_RenderPresent(p.backend->ren);
    SDL_SetRenderDrawColor(p.backend->ren, 28, 28, 48, 0);
    SDL_RenderClear(p.backend->ren);
    SDL_SetRenderDrawColor(p.backend->ren, 0, 0, 0, 0);
    SDL_Rect gameRect = (SDL_Rect){p.gameRect.x, p.gameRect.y, p.gameRect.w, p.gameRect.h};
    SDL_RenderFillRect(p.backend->ren, &gameRect);
}

Image CreateBatch(unsigned char *data, const char* tileset){
    
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
