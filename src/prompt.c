/* Print shell prompt */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <pwd.h>
#include <sys/types.h>
#include "prompt.h"

int prompt_mode = 0;
const char *hme;

static char cwd[PATH_MAX];

#ifndef HOST_NAME_MAX
/* HOST_NAME_MAX not available on some platforms */
static char hst[_POSIX_HOST_NAME_MAX + 1 /* \0 */];
#else
static char hst[HOST_NAME_MAX + 1 /* \0 */];
#endif

static const char *usr;

void prompt(void)
{
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("sheesh");
        exit(EXIT_FAILURE);
    }
    switch (prompt_mode)
    {
        case 0: printf("[%s]$ ", cwd); break;
        case 1: printf("[%s %s]$ ", usr, cwd); break;
        case 2: printf("[%s@%s %s]$ ", usr, hst, cwd); break;
    }
}

void log_user(void)
{
    struct passwd *pw;
    uid_t pw_uid;

    pw_uid = geteuid();
    pw = getpwuid(pw_uid);

    hme = pw->pw_dir;
    gethostname(hst, sizeof(hst));

    usr = pw->pw_name;

    chdir(hme);
    getcwd(cwd, sizeof(cwd));
}
