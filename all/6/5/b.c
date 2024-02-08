#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int executeCommand(char* command) {
    pid_t pid;
    int status;

    // Create a child process
    pid = fork();

    if (pid == -1) {
        // Error occurred while forking
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process

        // Tokenize the command into arguments
        char* argv[100];
        int argc = 0;
        char* token = strtok(command, " \t\n");
        while (token != NULL) {
            argv[argc++] = token;
            token = strtok(NULL, " \t\n");
        }
        argv[argc] = NULL;

        // Execute the command
        execvp(argv[0], argv);

        // If execvp returns, there was an error
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        // Parent process

        // Wait for the child process to terminate
        waitpid(pid, &status, 0);

        // Check if the child process terminated successfully
        if (WIFEXITED(status)) {
            // Return the exit status of the child process
            return WEXITSTATUS(status);
        }
    }

    return -1; // Default error status
}

int main() {
    char command[100];

    while (1) {
        // Prompt the user to enter a command
        printf("Shell> ");
        fgets(command, sizeof(command), stdin);

        // Remove newline character from the command
        if (command[strlen(command) - 1] == '\n') {
            command[strlen(command) - 1] = '\0';
        }

        // Check if the user entered "exit" to quit the shell
        if (strcmp(command, "exit") == 0) {
            break;
        }
	int previousExitStatus;
        // Check if the user entered "echo $?" to print the exit status
        if (strcmp(command, "echo $?") == 0) {
            printf("Previous exit status: %d\n", previousExitStatus);
            continue;
        }

        // Execute the user command
        int exitStatus = executeCommand(command);

        // Store the exit status of the command
        previousExitStatus = exitStatus;
    }

    return 0;
}

