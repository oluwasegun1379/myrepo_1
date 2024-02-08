#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void execute_command(char *command) {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        execlp("/bin/sh", "sh", "-c", command, NULL);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Parent process
        wait(NULL);
    } else {
        // Error forking
        perror("fork");
        exit(EXIT_FAILURE);
    }
}

int main(void) {
    char command[100];

    while (1) {
        printf("Shell> ");
        fgets(command, sizeof(command), stdin);

        // Remove trailing newline character from input
        size_t len = strlen(command);
        if (command[len - 1] == '\n') {
            command[len - 1] = '\0';
        }

        // Execute the command
        execute_command(command);
    }

    return 0;
}

