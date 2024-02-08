#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define CMD_BUF_SIZE 1024

void execute_command(const char* cmd);

int main(int argc, char *argv[]) {
    char cmd[CMD_BUF_SIZE];

    while (true) {
        // Print prompt
        printf("$ ");

        // Read user input
        if (fgets(cmd, CMD_BUF_SIZE, stdin) == NULL) {
            break;  // EOF or error, exit loop
        }

        // Strip newline from end of command string
        size_t len = strlen(cmd);
        if (len > 0 && cmd[len-1] == '\n') {
            cmd[len-1] = '\0';
        }

        // Execute command
        execute_command(cmd);
    }

    return 0;
}

void execute_command(const char* cmd) {
    if (strcmp(cmd, "ls") == 0) {
        system("ls");
    }
    else if (strcmp(cmd, "pwd") == 0) {
        system("pwd");
    }
    else if (strncmp(cmd, "echo ", 5) == 0) {
        // Skip "echo " prefix
        const char* arg = cmd + 5;
        printf("%s\n", arg);
    }
    else if (strcmp(cmd, "exit") == 0) {
        exit(0);
    }
    else {
        printf("Error, '%s' is not a command!\n", cmd);
    }
}

