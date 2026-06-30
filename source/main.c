#include <pthread.h>
#include <stdio.h>
#include "console.h"
#include "platform.h"
#include "tilesets.h"

int main(void){
    if(init_console()){
        printf("failed to initialize console\n");
        return 1;
    }

    printf("initialized console\n");

    Platform p = InitPlatform();

    Image test = LoadImage(p, "resources/test.png"); 

    Tileset *set = LoadTileset(p, "resources/test.png");

    Rect rect = {0, 0, 16, 16};

    while(p.running){
	ConsumeInput(&p);
	PutSrpite(p, test, rect, rect);
        execute_commands();
	PresentPlatform(p);
    }

    QuitPlatform(p);
    terminate_console();
    printf("terminated console\n");
    return 0;
}
