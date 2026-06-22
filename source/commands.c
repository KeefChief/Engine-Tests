#include "commands.h"
#include "entity.h"
#include <stdio.h>
#include <stdlib.h>

int cmd_echo(int argc, char **argv){
    if(argc != 2){
        printf("Usage:\n->echo <value to echo out>\n");
        return 0;
    }
    printf("%s\n",argv[1]);
    return 1;
}

int cmd_spawn_entity(int argc, char **argv){
    if(argc != 4){
        printf("Command: spawn_entity needs 3 arguments\n");
        return 0;
    }
    create_entity(atoi(argv[1]), atoi(argv[2]), 0, 0, atoi(argv[3]));
    return 1;
}

Command commands[] = {
    {"echo", cmd_echo},
    {"spawn_entity", cmd_spawn_entity}
};

int command_count = sizeof(commands) / sizeof(commands[0]);
