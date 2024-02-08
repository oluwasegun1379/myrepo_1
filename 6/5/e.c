#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_ARGS 10

char** parse_cmd(const char* cmd) {
    char** args = malloc((MAX_ARGS + 1) * sizeof(char*));  // Allocate memory for arguments
    if (args == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    char* token;
    char* delimiter = " ";
    int i = 0;

    // Tokenize the command string by whitespace
    token = strtok((char*)cmd, delimiter);
    while (token != NULL && i < MAX_ARGS) {
        args[i] = strdup(token);  // Duplicate the token and store in the arguments array
        if (args[i] == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
        i++;
        token = strtok(NULL, delimiter);
    }
    args[i] = NULL;  // Set the last element of the array to NULL to indicate the end

    return args;
}
int setenv_command(char **args) {
    if (args[1] == NULL || args[2] == NULL) {
        fprintf(stderr, "setenv: Invalid syntax. Usage: setenv VARIABLE VALUE\n");
        return 1;
    }

    if (setenv(args[1], args[2], 1) != 0) {
        fprintf(stderr, "setenv: Failed to set environment variable.\n");
        return 1;
    }

    return 0;
}

int unsetenv_command(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "unsetenv: Invalid syntax. Usage: unsetenv VARIABLE\n");
        return 1;
    }

    if (unsetenv(args[1]) != 0) {
        fprintf(stderr, "unsetenv: Failed to unset environment variable.\n");
        return 1;
    }

    return 0;
}

int execute_builtin_command(char **args) {
    if (strcmp(args[0], "setenv") == 0) {
        return setenv_command(args);
    } else if (strcmp(args[0], "unsetenv") == 0) {
        return unsetenv_command(args);
    }

    return -1; // Not a builtin command
}

int main() {
    char *cmd = NULL;
    char **args;
    size_t n = 20;
    ssize_t len;

    while (1) {
        printf("my_shell$ ");

        if ((len = getline(&cmd, &n, stdin)) != -1) {
            if (cmd[len - 1] == '\n')
                cmd[len - 1] = '\0';

            args = parse_cmd(cmd);

            if (args[0] != NULL) {
                if (strcmp(args[0], "exit") == 0) {
                    break;
                } else {
                    int exitStatus = execute_builtin_command(args);
                    if (exitStatus == -1) {
                        // Handle non-builtin command execution
                    }
                }
            }
        } else {
            break;
        }
    }

    free(cmd);
    printf("Shell terminated.\n");

    return 0;
}

