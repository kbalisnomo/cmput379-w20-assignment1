#include "builtin.h"

char *builtin_str[] = {
    "exit",
    "jobs",
    "kill",
    "resume",
    "sleep",
    "suspend",
    "wait"
};

int shell_num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

void shell_exit() {
    exit(0);
}

void shell_jobs() {
    int line_count, processes, tot_utime, tot_stime;
    struct rusage usage, child_usage;
    long  user_time, sys_time, child_utime, child_stime;
    FILE *fp;
    processes = 0;
    //calculate user and sys times
    getrusage(RUSAGE_SELF, &usage);
    getrusage(RUSAGE_CHILDREN, &child_usage);
    user_time = usage.ru_utime.tv_sec + child_usage.ru_utime.tv_sec;
    sys_time = usage.ru_stime.tv_sec + child_usage.ru_stime.tv_sec;
    
    //print out jobs details
    printf("\nRunning processes:\n");

    //get # of processes
    char *ps = (char*)malloc(64*sizeof(char));
    sprintf(ps, "ps -g %d -o pid,stat,cputime,command | wc -l", (int)getpid());
    fp = popen(ps, "r");
    char buf[1024];
    if (fp == NULL) {
        perror("popen failed:");
        exit(-1);
    }
    line_count = fscanf(fp, "%d", &line_count);
    pclose(fp);

    //if there are processes print them out + details
    if (line_count > 0) {
        sprintf(ps, "ps -g %d -o pid,stat,cputime,command", (int)getpid());
        fp = popen(ps, "r");
        char buf[1024];
        if (fp == NULL) {
            perror("popen failed:");
            exit(-1);
        }
        //print header line
        if ((fgets(buf, 1024, fp)) != NULL) {
            printf("#  %s", buf);
        }
        processes = 0;
        while ((fgets(buf, 1024, fp)) != NULL) {
            printf("%d: %s", processes, buf);
            processes++;
        }
        pclose(fp);
    }
    printf("Processes =\t%5d active\n"
            "Completed processes:\n"
            "User time =\t%5ld seconds\n"
            "Sys  time =\t%5ld seconds\n\n", processes, user_time, sys_time);
}


void shell_kill(char *line) {
    char **args = get_args(line);
    kill(atoi(args[1]), SIGKILL);
}

void shell_resume(char *line) {
    char **args = get_args(line);
    kill(atoi(args[1]), SIGCONT);
}

void shell_sleep(char *line) {
    char **args = get_args(line);
    sleep(atoi(args[1]));
}

void shell_suspend(char *line) {
    char **args = get_args(line);
    kill(atoi(args[1]), SIGSTOP);
}

void shell_wait(char *line) {
    int status;
    char **args = get_args(line);
    waitpid(atoi(args[1]), &status, 0);
}

void foreground_execute(char *line) {
    FILE *fp;
    char buf[1024];
    fp = popen(line, "r");
    if (fp == NULL) {
        perror("popen failed:");
        exit(-1);    
    }
    while ((fgets(buf, 1024, fp)) != NULL) {
        printf("%s", buf);
    }
    pclose(fp);
}

void background_execute(char *line) {
    int fd[2];
    int read_fd, write_fd, arg_count;
    int rc = fork();
    char **args;
    args = get_args(line);

    // creating pipe
    pipe(fd);
    read_fd = fd[0];
    write_fd = fd[1];

    if (rc < 0) { //fork failed
        perror("fork failed");
        exit(-1);
    } else if (rc == 0) { //child process
        close(read_fd);
        dup2(write_fd, 1);
        close(write_fd);
        execvp(args[0], args);
    } else { //parent process
        close(write_fd);
        //handler for child
        signal(SIGCHLD, sig_handler);
    }
}