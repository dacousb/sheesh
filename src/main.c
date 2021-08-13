/*
 * sheesh
 * the standalone shell
 *
 * this software is free software,
 * released under MIT license
 *
 * a shell for unix
 * by dacousb
 */

/* The main loop of the sheesh shell */
#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "split.h"
#include "exec.h"
#include "prompt.h"
#include "history.h"

void sheesh_loop(void)
{
    char *line;
    char **args;
    int status;
    do
    {
        prompt();
        line = read_line();
        system("/bin/stty sane");
        if (line[0] != 0)
            to_history(line);
        args = split_line(line);
        status = exec(args);
    } while (status);
}

int main(void)
{
    log_user();      /* Get the current username and host name*/
    history_check(); /* Test if the history file is accessible */
    sheesh_loop();   /* Start the shell loop */
    return 0;
}
