/* History file management */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "history.h"
#include "prompt.h"

char *get_history(void)
{
    char *result = calloc(256, sizeof(char));
    strcat(result, hme);
    strcat(result, "/.sheesh_history");
    return result;
}

/* Before the shell starts, this is called
 * from the main function */
void history_check(void)
{
    if (access(get_history(), F_OK))
    {
        /* No history file found, then, create
         * a new one with a Welcome message */
        FILE *history = fopen(get_history(), "w+");
        fputs("echo Welcome to sheesh!\n", history);
        fclose(history);
    }
}

void to_history(char *line)
{
    FILE *history = fopen(get_history(), "a");
    if (history == NULL)
    {
        perror("to history");
        putchar('\r');
        exit(EXIT_FAILURE);
    }
    fprintf(history, "%s", line);
    if (line[strlen(line) - 1] != '\n')
        fprintf(history, "\n");
    fclose(history);
}

void print_history(void)
{
    FILE *history = fopen(get_history(), "r");
    char line[256];
    while (fgets(line, sizeof(line), history))
        printf("%s", line);
    fclose(history);
}

/* The length in lines of the history file */
int get_n_of_lines(void)
{
    int lines = 0;
    FILE *history = fopen(get_history(), "r");
    while (!feof(history))
    {
        if (fgetc(history) == '\n')
            lines++;
    }
    fclose(history);
    return lines;
}

/* Get the n line */
char *get_n_line(int n)
{
    FILE *history;
    int line = 0;
    char *buff = calloc(256, sizeof(char));
    history = fopen(get_history(), "r");
    while (fgets(buff, 256, history))
    {
        if (++line == n)
        {
            fclose(history);
            return buff;
        }
        /* Clear buffer */
        memset(buff, 0, 256);
    }
    fclose(history);
    return " ";
}
