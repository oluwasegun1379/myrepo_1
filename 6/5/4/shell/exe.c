#include "shell.h"
void execute_cmd(char *command, char *args[])
{
        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            execvp(command, args);
            perror("./shell"); // Error occurred if execvp returns
            exit(EXIT_FAILURE);
        } else if (pid > 0) {
            // Parent process
            wait(NULL); // Wait for the child process to complete
        } else {
            // Fork failed
            perror("fork");
        }
}
