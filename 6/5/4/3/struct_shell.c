#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 10
#define MAX_CMD_LEN 256

typedef struct {
    char name[MAX_CMD_LEN];
    char *args[MAX_ARGS];
    int arg_count;
    char output_file[MAX_CMD_LEN];  // New field for output file name
    int redirect_type;  // 0: no redirection, 1: overwrite (>), 2: append (>>)
} Command;

void read_cmd(char *cmd);
void parse_cmd(char *cmd, Command *command);
void execute_cmd(Command *command);

int main(void)
{
    char cmd[MAX_CMD_LEN];
    Command command;

    while (1)
    {
        read_cmd(cmd);
        parse_cmd(cmd, &command);

        if (strcmp(command.name, "exit") == 0)
            break;

        execute_cmd(&command);
    }

    return 0;
}

void read_cmd(char *cmd)
{
    printf("MyShell~> ");
    fgets(cmd, MAX_CMD_LEN, stdin);
    int len = strlen(cmd);
    if (cmd[len - 1] == '\n')
        cmd[len - 1] = '\0';
}

void parse_cmd(char *cmd, Command *command)
{
    char *token;
    int i = 0;
    command->redirect_type = 0;  // Initialize redirect type to 0

    token = strtok(cmd, " ");
    strcpy(command->name, token);
    command->arg_count = 0;

    while (token != NULL && i < MAX_ARGS - 1)
    {

        // Check for file redirection symbols
        if (token != NULL && (strcmp(token, ">") == 0 || strcmp(token, ">>") == 0))
        {
            command->redirect_type = (strcmp(token, ">") == 0) ? 1 : 2;  // Set redirect type
            token = strtok(NULL, " ");  // Move to next token
            if (token != NULL)
                strcpy(command->output_file, token);  // Store output file name
        }
        else if (token != NULL)
        {
            command->args[i] = token;
            command->arg_count++;
            i++;
        }
        token = strtok(NULL, " ");
    }
    command->args[i] = NULL;
}

void execute_cmd(Command *command)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        // Perform file redirection based on redirect type
        if (command->redirect_type == 1)
        {
            freopen(command->output_file, "w", stdout);  // Overwrite file
        }
        else if (command->redirect_type == 2)
        {
            freopen(command->output_file, "a", stdout);  // Append to file
        }

        if (execvp(command->name, command->args) == -1)
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
        perror("Error");
    }
}

