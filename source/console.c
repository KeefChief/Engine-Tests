#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdatomic.h>
#include "console.h"
#include "commands.h"

#define MAX_COMMANDS 64
#define MAX_COMMAND_SIZE 256
static char buffer[MAX_COMMANDS][MAX_COMMAND_SIZE];
static pthread_t c;
static int head = 0;
static int tail = 0;

int init_console(){
    if(pthread_create(&c, NULL, console_thread, NULL) != 0){
        return 1;
    }
    return 0;
}

void *console_thread(void *arg){
    while(1){
        char temp[MAX_COMMAND_SIZE];
        fgets(temp, MAX_COMMAND_SIZE, stdin);
        temp[strcspn(temp, "\n")] = '\0';
        strcpy(buffer[head], temp);
        head = (head + 1) % MAX_COMMANDS;
    }
}

void execute_commands(){
    while(tail != head){
        int argc = 0;
        char *argv[10];
        char *arg = strtok(buffer[tail], " ");
        while(arg != NULL){
            argv[argc++] = arg;
            arg = strtok(NULL, " ");
        }
        for(int i = 0; i < command_count; i++){
            if(strcmp(argv[0], commands[i].name) == 0){
                commands[i].func(argc, argv);
                break;
            }
        }
        tail = (tail + 1) % MAX_COMMANDS;
    }
}

void terminate_console(){
    pthread_cancel(c);
    pthread_join(c, NULL);
}
