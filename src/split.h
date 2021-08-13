#pragma once
#define TOK_BUFF_SIZE 64
#define TOK_DELIM "\t\r\n\a "

char **split_line(char *line);
