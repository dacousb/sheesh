/* Implementation of basic commands */
#include <stdio.h>
#include <unistd.h>
#include "builtins.h"
#include "prompt.h"

#define VERSION "0.3.1"

void built_help(void)
{
    printf("Usage: sheesh, version " VERSION "\n");
    printf("    help        display this help\n");
    printf("    cd          change wdirectory\n");
    printf("    prompt      change prompt modes\n");
    printf("    exit        exit the session\n");
    printf("    h/history   display commands history\n");
    printf("    version     display version info\n");
}

/* The usual change directory command */
void built_cd(char **args)
{
    if (chdir(args[1]))
        perror("cd");
}

void print_version(void)
{
    printf("sheesh, version " VERSION "\n");
    printf("Copyright (C) 2021 dacousb\n");
    printf("Released under MIT LICENSE\n");
    printf("Written by dacousb\n");
}

/* Customize the prompt mode for that session */
void prompt_modes(char **args)
{
    if (args[1])
    {
        switch (args[1][0])
        {
            case '0': prompt_mode = 0; break;
            case '1': prompt_mode = 1; break;
            case '2': prompt_mode = 2; break;
            default: printf("Not a valid mode!\n");
        }
    }
    else
    {
        printf("Usage: prompt [i], version " VERSION "\n");
        printf("    change prompt to [i] mode\n");
        printf("    0 - pwd\n");
        printf("    1 - usr pwd\n");
        printf("    2 - usr hst pwd\n");
    }
}
