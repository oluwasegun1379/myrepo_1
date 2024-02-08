#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    char command[100];

    // Prompt the user to enter a command
    printf("Enter a command: ");
    fgets(command, sizeof(command), stdin);

    // Remove newline character from the command
    if (command[strlen(command) - 1] == '\n') {
        command[strlen(command) - 1] = '\0';
    }

    // Create a child process
    pid_t pid = fork();

    if (pid == -1) {
        // Error occurred while forking
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process

        // Execute the command to get its exit status
        char* argv[] = {"/bin/sh", "-c", command, NULL};
        execve("/bin/sh", argv, NULL);

        // If execve returns, there was an error
        perror("execve");
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

