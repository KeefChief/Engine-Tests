#ifndef COMMANDS_H
#define COMMANDS_H

typedef int (*cmd_fn)(int argc, char **argv);

typedef struct Command{   
    const char *name;
    cmd_fn func;
}Command;

extern Command commands[];

//nb of commands
extern int command_count;

//commands functions themselves
int cmd_echo(int argc, char **argv);
int cmd_spawn_entity(int argc, char **argv);

#endif