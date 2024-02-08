#include "shell.h"
void parse_cmd(char *command, char **args) {
    char *token;
    int i = 0;                                                                                                  if (command == NULL)
            return;
    token = my_strtok(command, " ");
    while (token != NULL && i < MAX_ARGS - 1) {               args[i] = token;
        i++;                                                  token = strtok(NULL, " ");                        }                                                     args[i] = NULL;
}
