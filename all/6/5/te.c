#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

#define ARG_COUNT 100

extern char **environ;

char **parse_cmd(char *cmd);
void execute_cmd(char **argv);

int main(void)
{
    char *cmd = NULL;
    char **argv;
    size_t n = 20;
    ssize_t len;

    printf("new~shell$ ");

    while ((len = getline(&cmd, &n, stdin)) != -1)
    {
        if (cmd[len - 1] == '\n')
            cmd[len - 1] = '\0';

        argv = parse_cmd(cmd);
        execute_cmd(argv);

        printf("new~shell$ ");
    }
    free(cmd);
    exit(EXIT_SUCCESS);
}

char **parse_cmd(char *cmd)
{
    char *token;
    size_t i = 0;
    char **argv;
    argv = malloc(sizeof(char *) * (ARG_COUNT + 1));

    if (cmd == NULL || argv == NULL)
        return NULL;

    token = strtok(cmd, " ");
    while (token != NULL && i < ARG_COUNT)
    {
        argv[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    argv[i] = NULL;
    return argv;
}

void execute_cmd(char **argv)
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        char *cmd = argv[0];

        // Check if the command is a relative or absolute path
        if (strchr(cmd, '/') == NULL)
        {
            // Command is a relative path, search for it in the directories of PATH
            char *path = getenv("PATH");
            char *dir;
            char *token;

            // Copy the path variable to a temporary string for tokenization
            char *path_copy = strdup(path);

            // Tokenize the path variable using ':' delimiter
            token = strtok(path_copy, ":");
            while (token != NULL)
            {
                char *full_path = malloc(strlen(token) + strlen(cmd) + 2);
                strcpy(full_path, token);
                strcat(full_path, "/");
                strcat(full_path, cmd);

                // Check if the command exists at the constructed path
                if (access(full_path, X_OK) == 0)
                {
                    // Command found, replace the argv[0] with the full path
                    argv[0] = full_path;
                    execve(full_path, argv, environ);

                    // If execve fails, free the allocated memory and exit
                    perror("execve");
                    free(full_path);
                    exit(1);
                }

                // Free the memory allocated for the full path
                free(full_path);

                // Move to the next directory in the path
                token = strtok(NULL, ":");
            }

            // Command not found in any directory of the path, print an error
            fprintf(stderr, "Command not found: %s\n", cmd);
            exit(1);
        }
        else
        {
            // Command is an absolute path, execute it directly
            execve(cmd, argv, environ);

            // If execve fails, print an error and exit
            perror("execve");
            exit(1);
        }
    }
    else if (pid > 0)
    {
        wait(NULL);
    }
    else if (pid == -1)
    {
        perror("fork");
        exit(1);
    }
   
}
