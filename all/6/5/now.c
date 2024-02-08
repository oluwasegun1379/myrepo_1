#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100

int main() {
    char command[MAX_COMMAND_LENGTH];

    printf("Enter a command to execute: ");
    fgets(command, MAX_COMMAND_LENGTH, stdin);

    // Remove trailing newline character from the command
    command[strcspn(command, "\n")] = '\0';

    // Create a child process
    pid_t pid = fork();

    if (pid == -1) {
        // Error occurred while forking
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process

        // Execute the user-entered command
        execlp(command, command, NULL);

        // If execlp returns, there was an error
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        // Parent process

        // Wait for the child process to terminate
        int status;
        waitpid(pid, &status, 0);

        // Check if the child process terminated successfully
        if (WIFEXITED(status)) {
            // Print the exit status of the child process
            printf("Exit status: %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}

