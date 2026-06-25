#include <pthread.h>
#include <stdio.h>
#include "console.h"
#include "platform.h"

int main(int argc, char** argv){
    if(init_console()){
        printf("failed to initialize console\n");
        return 1;
    }

    printf("initialized console\n");

    Platform_Window *win = platform_init_window(640, 480, "AAAAAA");
    printf("Initialized window !\n");
    Event e;

    int running = 1;

    while(running){
	while(platform_get_event(&e, win)){
	    switch(e.type){
		case WINDOW_CLOSED:
		    printf("Window closed !\n");
		    running = 0;
		    break;
	    }
	}
        execute_commands();
    }

    platform_close_window(win);
    terminate_console();

    printf("terminated console\n");
    return 0;
}
