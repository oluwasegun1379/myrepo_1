#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>

#define BUFSIZE 1024
#define ARG_COUNT 10

void read_cmd(char *cmd);
void execute_cmd(char *args[]);
void parse_cmd(char *cmd, char *args[]);

int main(void)
{
    char cmd[BUFSIZE];
    char *args[ARG_COUNT];

    while (true)
    {
        read_cmd(cmd);
        parse_cmd(cmd, args);

        if (args[0] == NULL)
            continue;

        if (strcmp(args[0], "exit") == 0)
            break;
        else if (strcmp(args[0], "cd") == 0)
        {
            if (args[1] == NULL)
                printf("Expected an argument after \"cd\"\n");
            else if (chdir(args[1]) != 0)
                perror("Error");
        }
        else
            execute_cmd(args);
    }

    return EXIT_SUCCESS;
}

void read_cmd(char *cmd)
{
    printf("Myshell~> ");
    fgets(cmd, BUFSIZE, stdin);
    cmd[strcspn(cmd, "\n")] = '\0';  // Remove trailing newline
}

void parse_cmd(char *cmd, char *args[])
{
    char *token;
    int i = 0;

    token = strtok(cmd, " ");
    while (token != NULL && i < ARG_COUNT - 1)
    {
        args[i] = token;
        token = strtok(NULL, " ");
        i++;
    }
    args[i] = NULL;
}

void execute_cmd(char *args[])
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        if (execvp(args[0], args) == -1)
        {
            perror("Error");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid > 0)
    {
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    else
    {
        perror("Error forking");
    }
}

