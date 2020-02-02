#include "shell379.h"

int main(int argc, char *argv[]) {
    char line[LINE_LENGTH];
    int len;
    while (1) {
        printf("SHELL379: ");
        fgets(line, sizeof line, stdin);
        len = strlen(line);
        if (strlen(line) > 0 && line[len-1] == '\n') {
            line[len-1] = 0;
        }
        int job_no;
        int built_in;
        built_in  = 0;
        for (int i = 0; i < shell_num_builtins(); i++) {
            if (strstr(line, "exit") != NULL) {
                built_in = 1;
            }
            else if (strstr(line, "jobs")) {
                built_in = 2;
            }
            else if (strstr(line, "kill")) {
                built_in = 3;
            }
            else if (strstr(line, "resume")) {
                built_in = 4;
            }
            else if (strstr(line, "sleep")) {
                built_in = 5;
            }
            else if (strstr(line, "suspend")) {
                built_in = 6;
            }
            else if (strstr(line, "wait")) {
                built_in = 7;
            }
        }

        // Perform built-in or execute command
        switch (built_in)
        {
        case 1:
            shell_exit();
            break;
        case 2:
            shell_jobs();
            break;
        case 3:
            shell_kill(line);
            break;
        case 4:
            shell_resume(line);
            break;
        case 5:
            shell_sleep(line);
            break;
        case 6:
            shell_suspend(line);
            break;
        case 7:
            shell_wait(line);
            break;
        default:
            if (strlen(line) > 0 && line[strlen(line)-1] == '&') {
                background_execute(line);
            }
            else {
                foreground_execute(line);
            }
            break;
        }
    }


    return 0;
}