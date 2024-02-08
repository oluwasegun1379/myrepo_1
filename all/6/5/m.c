#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>

#define ARG_COUNT 100

extern char **environ;

typedef struct
{
        int redirect_num;
        char output_file_name[ARG_COUNT];
} red_t;

char **parse_cmd(char *cmd);
void execute_cmd(char **argv);
char *add_abs_path_to_cmd(char *cmd);
void my_print(const char *message);
void check_file_redirection(red_t *red, char *token);
void execute_red(red_t *red);

int main(void)
{
        char *cmd = NULL;
        char **argv;
        size_t n = 20;
        ssize_t len;

        my_print("new~shell$ ");

        while ((len = getline(&cmd, &n, stdin)) != -1)
        {
                if (cmd[len - 1] == '\n')
                        cmd[len - 1] = '\0';

                argv = parse_cmd(cmd);
                execute_cmd(argv);

                my_print("new~shell$ ");
        }
        free(cmd);
        _exit(EXIT_SUCCESS);
}

char **parse_cmd(char *cmd)
{
    char *token;
    size_t i = 0;
    char **argv;
    red_t var = {0};

    argv = malloc(sizeof(char *) * (ARG_COUNT + 1));

    if (cmd == NULL || argv == NULL)
        return NULL;

    token = strtok(cmd, " ");
    while (token != NULL && i < ARG_COUNT)
    {
        check_file_redirection(&var, token);

        if (var.redirect_num == 0)
        {
            argv[i] = token;
            i++;
        }
        else if (var.redirect_num == 1 || var.redirect_num == 2)
        {
            token = strtok(NULL, " ");
            if (token != NULL)
            {
                strncpy(var.output_file_name, token, ARG_COUNT - 1);
                token = strtok(NULL, " ");  // Skip the file name token
            }
        }

        if (token != NULL)
        {
            check_file_redirection(&var, token);
            if (var.redirect_num == 0)
            {
                argv[i] = token;
                i++;
            }
        }

        token = strtok(NULL, " ");
    }
    argv[i] = NULL;
    return argv;
}


void execute_cmd(char **argv)
{
        pid_t pid;
        red_t var = {0};

        pid = fork();
        if (pid == 0)
        {
                argv[0] = add_abs_path_to_cmd(argv[0]);
                execute_red(&var);
                if (execve(argv[0], argv, environ) == -1)
                {
                        perror("execve");
                        _exit(1);
                }
        }
        else if (pid > 0)
        {
                wait(NULL);
        }
        else if (pid == -1)
        {
                perror("fork");
                _exit(1);
        }
        free(argv);
}

char *add_abs_path_to_cmd(char *cmd)
{
    char *path = getenv("PATH");
    char *path_copy;
    char *full_path;
    char *dir;
    char *token;

    if (strchr(cmd, '/') != NULL)
    {
        // If the command contains a slash (/), it's already an absolute path
        return cmd;
    }

    // Copy the path variable to a temporary string for tokenization
    path_copy = strdup(path);

    // Tokenize the path variable using ':' delimiter
    token = strtok(path_copy, ":");
    while (token != NULL)
    {
        full_path = malloc(strlen(token) + strlen(cmd) + 2);
        strcpy(full_path, token);
        strcat(full_path, "/");
        strcat(full_path, cmd);

        // Check if command exists at the constructed path
        if (access(full_path, X_OK) == 0)
        {
            // Command found
            free(path_copy);
            return full_path;
        }
        free(full_path);
        token = strtok(NULL, ":");
    }

    // Command not found
    free(path_copy);
    return NULL;
}

void my_print(const char *message)
{
        write(STDOUT_FILENO, message, strlen(message));
}

void check_file_redirection(red_t *red, char *token)
{
        red->redirect_num = 0;
        if (strcmp(token, ">") == 0)
        {
                red->redirect_num = 1;
                token = strtok(NULL, " ");
                if (token != NULL)
                        strncpy(red->output_file_name, token, ARG_COUNT - 1);
        }
        else if (strcmp(token, ">>") == 0)
        {
                red->redirect_num = 2;
                token = strtok(NULL, " ");
                if (token != NULL)
                        strncpy(red->output_file_name, token, ARG_COUNT - 1);
        }
}

void execute_red(red_t *red)
{
        int fd;

        if (red == NULL)
                return;

        if (red->redirect_num == 1)
        {
                fd = open(red->output_file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd == -1)
                {
                        perror("open");
                        exit(EXIT_FAILURE);
                }
                dup2(fd, STDOUT_FILENO);
        }
        else if (red->redirect_num == 2)
        {
                fd = open(red->output_file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (fd == -1)
                {
                        perror("open");
                        exit(EXIT_FAILURE);
                }
                dup2(fd, STDOUT_FILENO);
        }

        fflush(stdout);
        close(fd);
}

