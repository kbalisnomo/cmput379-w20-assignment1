#ifndef BUILTIN_H
#define BUILTIN_H
#include <stdio.h>
#include <sys/resource.h>
#include <signal.h>
#include "utils.h"
int shell_num_builtins();
void shell_exit();
void shell_jobs();
void shell_kill(char *line);
void shell_resume(char *line);
void shell_sleep(char*line);
void shell_suspend(char *line);
void shell_wait(char *line);
void foreground_execute(char *line);
void background_execute(char *line);

#endif