/* Command execution */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "exec.h"
#include "builtins.h"
#include "history.h"

int exec(char **args)
{
    if (args[0])
    {
        if (!strcmp(args[0], "cd"))
            built_cd(args);
        else if (!strcmp(args[0], "exit"))
            exit(EXIT_SUCCESS);
        else if (!strcmp(args[0], "help"))
            built_help();
        else if (!strcmp(args[0], "history") || !strcmp(args[0], "h"))
            print_history();
        else if (!strcmp(args[0], "prompt"))
            prompt_modes(args);
        else if (!strcmp(args[0], "version"))
            print_version();
        else
            return exec_process(args);
    }
    return -1;
}

int exec_process(char **args)
{
    pid_t pid = fork(), wpid;
    int status;

    if (!pid)
    {
        if (execvp(args[0], args) == -1)
            fprintf(stderr, "sheesh: %s: command not found\n", args[0]);
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
        perror("sheesh");
    else
    {
        do
            wpid = waitpid(pid, &status, WUNTRACED);
        while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}
