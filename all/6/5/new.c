#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_ARGS 10
#define MAX_INPUT_SIZE 1024

// Function to handle file redirection
void handle_redirection(char *command[], char *input_file, char *output_file) {
    int fd_in, fd_out;
    
    if (input_file != NULL) {
        fd_in = open(input_file, O_RDONLY);
        if (fd_in < 0) {
            perror("Error opening input file");
            exit(1);
        }
        dup2(fd_in, STDIN_FILENO);
        close(fd_in);
    }
    
    if (output_file != NULL) {
        fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_out < 0) {
            perror("Error opening output file");
            exit(1);
        }
        dup2(fd_out, STDOUT_FILENO);
        close(fd_out);
    }
    
    execvp(command[0], command);
    perror("Error executing command");
    exit(1);
}

int main() {
    char input[MAX_INPUT_SIZE];
    char *command[MAX_ARGS];
    char *token;
    char *input_file = NULL;
    char *output_file = NULL;
    int i, background;

    while (1) {
        printf("Shell> ");
        fgets(input, MAX_INPUT_SIZE, stdin);

        // Remove trailing newline character
        input[strcspn(input, "\n")] = '\0';

        // Check for background execution
        background = 0;
        if (input[strlen(input) - 1] == '&') {
            background = 1;
            input[strlen(input) - 1] = '\0';
        }

        // Tokenize the input
        token = strtok(input, " ");
        i = 0;
        while (token != NULL && i < MAX_ARGS - 1) {
            if (strcmp(token, "<") == 0) {
                // Input file redirection
                token = strtok(NULL, " ");
                input_file = token;
            } else if (strcmp(token, ">") == 0) {
                // Output file redirection
                token = strtok(NULL, " ");
                output_file = token;
            } else {
                command[i++] = token;
            }
            token = strtok(NULL, " ");
        }
        command[i] = NULL;

        pid_t pid = fork();
        if (pid == -1) {
            perror("Error forking process");
            exit(1);
        } else if (pid == 0) {
            // Child process
            handle_redirection(command, input_file, output_file);
        } else {
            // Parent process
            if (!background) {
                // Wait for the child process to complete
                wait(NULL);
            }
        }

        // Reset file redirection variables
        input_file = NULL;
        output_file = NULL;
    }

    return 0;
}

