#ifndef CONSOLE_H
#define CONSOLE_H

int init_console();
void *console_thread(void *arg);
void execute_commands();
void terminate_console();

#endif