#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

extern char **environ;

void line_interpreter();
char *_strchr(const char *s, int c);
char **parse_cmd(char *cmd);
char *_strtok(char *string, const char *delimeter);
int execute_cmd(char **argv);
char *add_abs_path_to_cmd(char *cmd);

#endif /* SHELL_H */
