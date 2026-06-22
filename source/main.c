#include <pthread.h>
#include <stdio.h>
#include "console.h"
#include "raylib.h"

int main(int argc, char** argv){
    if(init_console()){
        printf("failed to initialize console\n");
        return 1;
    }
    printf("initialized console\n");

    InitWindow(320, 240, "TEST");
    SetTargetFPS(30);

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        DrawFPS(10, 10);
        EndDrawing();
        execute_commands();
    }

    printf("terminating console\n");
    terminate_console();

    return 0;
}