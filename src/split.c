/* Split the command so that it can
 * be interpreted correctly */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "split.h"

char **split_line(char *line)
{
    size_t bufsize = TOK_BUFF_SIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens)
    {
        fprintf(stderr, "sheesh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TOK_DELIM);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += TOK_BUFF_SIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                fprintf(stderr, "sheesh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}
