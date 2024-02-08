#ifndef SHELL_H
#define SHELL_H

extern char **environ;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 100
void read_cmd(char **cmd);
void parse_cmd(char *command, char **args);
void execute_cmd(char *command, char *args[]);
int commandExists(const char *command);
void print_env();
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
char* my_strtok(char* str, const char* delimiters);

#endif
