/* Input library.
 * It is integrated with the shell functionality,
 * but can be used independently (with some tweaks)
 * for other projects
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "history.h"
#include "prompt.h"
#include "completion.h"
#include "colors.h"

#define ETX 3
#define TAB 9
#define CR 13
#define ESC 27
#define SQB 91
#define DEL 127

char *read_line(void)
{
    char *line = calloc(256, sizeof(char));

    /* Store the last completion length to clear
     * it later */
    size_t last_completion_len = 0;

    /* The "substraction" variable, allows us
     * to iterate through the history file*/
    int subs = -1;

    /* "getchar" directly and do not print
     * what is entered, we will take care of
     * printing it once we have checked it*/
    system("/bin/stty raw -echo");

    /* The input line will be stored as a "tape" */
    for (size_t i = 0; i < 256; i++)
    {
        char c = getchar();
        if (line[0] == 0)
            i = 0;
        if (i > strlen(line))
            i = strlen(line);

        /* Check the entered character */
        if (c == ETX)
        {
            printf("\r\n");
            return "";
        }
        else if (c == TAB)
        {
            /* Autocompletion with tab */
            char *result = find(line);
            if (result)
            {
                printf("\r");
                prompt();
                for (size_t pos = 0; pos < 256; pos++)
                {
                    if (result[pos] == 0)
                        break;
                    line[pos] = result[pos];
                    putchar(line[pos]);
                    i = pos;
                }
            }
        }
        else if (c == ESC)
        {
            if (getchar() != SQB) /* [ */
            {
                printf("\a\r\n");
                return "";
            }
            char code = getchar();
            switch (code)
            {
            case 'A': /* Arrow up */
            case 'B': /* Arrow down */
                printf("\r");
                for (int j = 0; j < i + 30; j++) /* 30 is ~prompt size */
                    putchar(' ');                /* Clean the current line */

                if (code == 'A' && subs < get_n_of_lines() - 1)
                    subs++;
                if (code == 'B' && subs > 0)
                    subs--;

                printf("\r");
                prompt();
                line = get_n_line(get_n_of_lines() - subs);
                if (line[strlen(line) - 1] == '\n')
                    line[strlen(line) - 1] = 0;
                i = strlen(line) + 1;

                printf("%s", line);
                break;
            case 'C': /* Arrow right */
                if (i <= strlen(line))
                {
                    putchar('\r');
                    prompt();
                    for (size_t pos = 0; pos <= i; pos++)
                        putchar(line[pos]);
                }
                break;
            case 'D': /* Arrow left */
                if (i > 1)
                {
                    i -= 2;
                    putchar('\r');
                    prompt();
                    for (size_t pos = 0; pos <= i; pos++)
                        putchar(line[pos]);
                }
                else if (i == 1)
                {
                    i = -1;
                    putchar('\r');
                    prompt();
                }
                break;
            }
        }
        else if (c == DEL)
        {
            if (i > 0)
            {
                if (i < strlen(line))
                {
                    for (size_t move = i - 1; move < strlen(line); move++)
                        line[move] = line[move + 1];
                    putchar('\r');
                    prompt();
                    printf("%s ", line);
                    i -= 2;
                    for (size_t j = i; j < strlen(line); j++)
                        printf("\033[1D");
                }
                else
                {
                    line[--i] = 0;
                    --i;
                    printf("\033[1D \033[1D");
                }
            }
        }
        else if (c == CR)
        {
            printf("\r\n");
            return line;
        }
        else
        {
            if (i < strlen(line))
            {
                for (size_t move = strlen(line) + 1; move >= i && move > 0; move--)
                    if (line[move - 1] != 0)
                        line[move] = line[move - 1];
                putchar('\r');
                prompt();
                line[i] = c;
                printf("%s", line);

                for (int j = 0; j < last_completion_len; j++)
                    putchar(' ');
                for (int j = 0; j < last_completion_len; j++)
                    printf("\033[1D");

                for (size_t j = strlen(line); j > i + 1; j--)
                    printf("\033[1D");
            }
            else
            {
                line[i] = c;
                putchar(c);
            }
        }

        /* Autosuggestions while typing */
        char *completion = find(line);
        if (i == strlen(line) - 1)
        {
            if (completion)
            {
                printf(BLUE);
                for (size_t pos = i + 1; pos < strlen(completion); pos++)
                    putchar(completion[pos]);
            }

            for (int j = 0; j < last_completion_len; j++)
                putchar(' ');
            for (int j = 0; j < last_completion_len; j++)
                printf("\033[1D");

            if (completion)
            {
                for (int j = strlen(completion) - i - 1; j > 0; j--)
                    printf("\033[1D");
                printf(RESET);
                last_completion_len = strlen(completion);
            }
        }
    }
    return "ERROR";
    /* Too long command */
}
