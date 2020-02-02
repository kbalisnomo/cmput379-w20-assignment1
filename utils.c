#include "utils.h"

char **get_args(char *line) {
    // allocate memory for args (7) of size (20)
    char **args = malloc(MAX_ARGS * sizeof(char*));
    for (int i = 0; i < MAX_ARGS; i++)
        args[i] = malloc(MAX_LENGTH * sizeof(char));
    int arg_count;
    char *token;
    // tokenize input
    arg_count = 0;
    token = strtok(line, " ");
    args[arg_count] = token;
    while(token != NULL) {
        args[arg_count] = token;
        token = strtok(NULL, " ");
        arg_count++;
    }
    args[arg_count] = 0;

    return args;
}

void sig_handler(int signum) {
    int status;
    waitpid(-1, &status, WNOHANG);
}