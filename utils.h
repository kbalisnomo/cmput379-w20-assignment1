#ifndef UTILS_H
#define UTILS_H
#define MAX_ARGS 7        // Max # of arguments to a command
#define MAX_LENGTH 20     // Max # of characters in an argument
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
char **get_args(char *line);
void sig_handler(int signum);
#endif