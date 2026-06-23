#include <pthread.h>
#include <stdio.h>
#include "console.h"

int main(int argc, char** argv){
    if(init_console()){
        printf("failed to initialize console\n");
        return 1;
    }
    printf("initialized console\n");

    while(1){
        execute_commands();
    }

    printf("terminating console\n");
    terminate_console();

    return 0;
}
