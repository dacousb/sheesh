/* Autocompletion (algorithms) */
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "completion.h"

/* Print the installed programs */
void p_all_programs(void)
{
    DIR *bin;
    struct dirent *dir;
    bin = opendir("/usr/bin");
    if (bin)
    {
        while ((dir = readdir(bin)) != NULL)
            printf("%s\n", dir->d_name);
        closedir(bin);
    }
}

/* Get the n file of the bin directory
 * This might change in the future to a
 * cleaner and more effective algorithm */
char *find_n(int n)
{
    char *result = NULL;
    int curr_n = 0;
    DIR *bin;
    struct dirent *dir;
    bin = opendir("/usr/bin");
    if (bin)
    {
        while ((dir = readdir(bin)) != NULL)
        {
            if (curr_n == n)
            {
                result = dir->d_name;
                break;
            }
            curr_n++;
        }
    }
    return result;
}

char *find(char line[256])
{
    char *result;
    int match[2] = {0, 0};  /* The most accurate match as scan goes on */
    int cmatch[2] = {0, 0}; /* The current match */

    DIR *bin;
    struct dirent *dir;
    bin = opendir("/usr/bin");
    if (bin)
    {
        while ((dir = readdir(bin)) != NULL)
        {
            for (size_t pos = 0; pos < 256; pos++)
            {
                if (dir->d_name[pos] == line[pos] && ++cmatch[1] > match[1])
                {
                    match[0] = cmatch[0];
                    match[1] = cmatch[1];
                }
                else
                    break;
            }
            cmatch[0]++;
            cmatch[1] = 0;
        }
        closedir(bin);
    }
    result = find_n(match[0]);

    int last_check = 1;
    for (size_t len = 0; len < strlen(line); len++)
        if (line[len] != result[len])
            last_check = 0;

    if (match[0] > 0 && strlen(result) > strlen(line) && last_check)
        return result;
    else
        return NULL;
}
