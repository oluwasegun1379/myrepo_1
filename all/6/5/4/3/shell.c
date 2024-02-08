#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10

void readCommand(char *command) {
    printf("Shell> ");
    fgets(command, MAX_COMMAND_LENGTH, stdin);

    // Remove trailing newline character
    if (command[strlen(command) - 1] == '\n') {
        command[strlen(command) - 1] = '\0';
    }
}

void parseCommand(char *command, char **args) {
    char *token;
    int i = 0;

    if (command == NULL)
	    return;
    token = strtok(command, " ");
    while (token != NULL && i < MAX_ARGS - 1) {
        args[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;
}

void executeCommand(char **args) {
    pid_t pid;
    int status;

    if (*args == NULL)
	    return;
    pid = fork();

    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            perror("Shell");
        }
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Parent process
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    } else {
        // Error forking
        perror("Shell");
    }
}

int main() {
    char command[MAX_COMMAND_LENGTH];
    char *args[MAX_ARGS];

    while (1) {
        readCommand(command);
        parseCommand(command, args);

        if (strcmp(args[0], "exit") == 0) {
            break;
        }
	else if (strcmp(args[0], "#") == 0)
		return (0);
	else if (strcmp(args[0], "cd") == 0) {
            if (args[1] == NULL) {
                printf("Shell: Expected argument to \"cd\"\n");
            } else {
                if (chdir(args[1]) != 0) {
                    perror("Shell");
                }
            }
        } else {
            executeCommand(args);
        }
    }

    return 0;
}

