#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>

//#define ARG_COUNT 100

extern char **environ;

typedef struct
{
    int redirect_num;
    char *output_file_name;
} red_t;

char **parse_cmd(char *cmd);
int execute_cmd(char **argv, char *cmd);
char *add_abs_path_to_cmd(char *cmd);
void my_print(const char *message);
int builtin(char **argv);
void print_env();
char *remove_comment(char *cmd);
void exitStatus();
void p_int(int number);
int redirect_number(char *cmd);
char *output_name(char *cmd);
char *_strtok(char *cmd, const char *delim);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

int main(void)
{
        int previousExitStatus = 0;
        int exitStatus;
        char *cmd = NULL;
        char *cmd_copy = NULL;
        char **argv;
        size_t n = 0;
        ssize_t len;
        int i;
        int check = 0;

                my_print("new~shell$ ");

        while((len = _getline(&cmd, &n, stdin)) != -1)
        {
                        if (cmd[len - 1] == '\n')
                        cmd[len - 1] = '\0';
                        check = 1;
                        cmd_copy = strndup(cmd, strlen(cmd));
                        if (strlen(cmd) == 0)
                        {
                                my_print("new~shell$ ");
                                continue;
                        }

                        cmd = remove_comment(cmd);
                        argv = parse_cmd(cmd);

                        if (strcmp(argv[0], "echo") == 0 && argv[1] != NULL && strcmp(argv[1], "$?") == 0)
                        {
                                p_int(previousExitStatus);
                                my_print("\n");
                                free(argv); //edited
                                my_print("new~shell$ ");
                                continue;
                        }

                        if (argv[0] != NULL)
                        {
                                if (strcmp(argv[0], "exit") == 0)
                                {
                                        break; // EOD
                                }

                                if (builtin(argv) == 1)
                                {
                                        exitStatus = execute_cmd(argv, cmd_copy);
                                        if (cmd_copy != NULL)
                                                free(cmd_copy); // edit
                                        previousExitStatus = exitStatus;
                                }
                        }
                my_print("new~shell$ ");
        }
        if (check)
        {
                int j, l = 0;
                for (j = 0; argv[j] != NULL; j++)
                        l++;
                for (i = 0; i < l; i++)
                        free(argv[i]);
                free(argv);
        }
        free(cmd);
        free(cmd_copy);

        my_print("logout\n");
        exit(EXIT_SUCCESS);
}
char **parse_cmd(char *cmd)
{
        char *token;
        int i = 0;
        char **argv = malloc(sizeof(char *) * (strlen(cmd) + 1));
        if (cmd == NULL || argv == NULL)
                return NULL;

        token = _strtok(cmd, " ");
        while (token != NULL)
        {
                if (strcmp(token, ">") == 0 || strcmp(token, ">>") == 0)
                {
                        red_t red;
                        red.redirect_num = strcmp(token, ">") == 0 ? 1 : 2;
                        token = _strtok(NULL, " ");
                        if (token != NULL)
                        {
                                red.output_file_name = token;
                                //strcpy(red.output_file_name, token);
                        }
                        argv[i] = (char *)malloc(sizeof(red_t));
                        memcpy(argv[i], &red, sizeof(red_t));
                }
                else
                {
                        argv[i] = strndup(token, strlen(token));
                }
                        i++;
                        token = _strtok(NULL, " ");
        }
        argv[i] = NULL;
        return argv;
}
int execute_cmd(char **argv, char *cmd)
{
        int status;
        pid_t pid;
        int redirect_n;
        char *cmd_copy = strndup(cmd, strlen(cmd));
        char *file_name;
        int i;

        pid = fork();
        if (pid == 0)
        {
                argv[0] = add_abs_path_to_cmd(argv[0]);
                redirect_n = redirect_number(cmd);


                if (redirect_n == 1)
                {
                        file_name = output_name(cmd_copy);
                        int fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                        if (fd == -1)
                        {
                                perror("open");
                                exit(1);
                        }
                        if (dup2(fd, STDOUT_FILENO) == -1)
                        {
                                perror("dup2");
                                exit(1);
                        }
                        close(fd);
                        free(file_name); // edited
                }
                else if (redirect_n == 2)
                {
                        file_name = output_name(cmd_copy);
                        int fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
                        if (fd == -1)
                        {
                                perror("open");
                                exit(1);
                        }
                        if (dup2(fd, STDOUT_FILENO) == -1)
                        {
                                perror("dup2");
                                exit(1);
                        }
                        close(fd);
                        free(file_name); // edited
                }

                if (execve(argv[0], argv, environ) == -1)
                {
                        perror("execve");
                        exit(1);
                }
        }
        else if (pid > 0)
        {
                waitpid(pid, &status, 0);
		printf("The PID = %d\n", pid);
                if (WIFEXITED(status))
                {
                        for (i = 0; argv[i] != NULL; i++)
                                free(argv[i]); // edit
                        free(argv);
                        free(cmd_copy);
                        return WEXITSTATUS(status);
                }
        }
        else
        {
                perror("fork failed");
                free(argv[0]); // edited
                free(argv);
                free(cmd_copy);
                exit(1);
        }

        for (i = 0; argv[i] != NULL; i++)
                free(argv[i]); // edit
        free(cmd); // edit
        free(argv[0]); // edited
        free(argv);
        free(cmd_copy);
        return -1;
}
char *add_abs_path_to_cmd(char *cmd)
{
        char *path = getenv("PATH");
        char *path_copy;
        char *full_path;
        char *dir;
        char *token;

        if (strchr(cmd, '/') == NULL)
        {
                path_copy = strndup(path, strlen(path));

                token = _strtok(path_copy, ":");
                while (token != NULL)
                {
                        full_path = malloc(strlen(token) + strlen(cmd) + 2);
                        strcpy(full_path, token);
                        strcat(full_path, "/");
                        strcat(full_path, cmd);

                        if (access(full_path, X_OK) == 0)
                        {
                                free(path_copy);
                                return full_path;
                        }

                        free(full_path);
                        token = _strtok(NULL, ":");
                }

                my_print(cmd);
                my_print(": Command not found\n");
                free(path_copy);
                exit(1);
        }
        else
        {
                return cmd;
        }
}

int builtin(char **argv)
{
        const char *homeDir;
        if (strcmp(argv[0], "cd") == 0)
        {
                if (argv[1] == NULL)
                {
                        homeDir = getenv("HOME");
                        if (chdir(homeDir) == -1)
                        my_print("Fail to change to home directory\n");
                }
                else if (chdir(argv[1]) != 0)
                {
                        perror("cd");
                }

                return 0;
        }
        else if (strcmp(argv[0], "env") == 0)
        {
                print_env();

                return 0;
        }

        return 1;
}

void print_env()
{
        char **env = environ;
        while (*env != NULL)
        {
                my_print(*env);
                my_print("\n");
                env++;
        }
}

char *remove_comment(char *cmd)
{
        char *comment_pos = strchr(cmd, '#');

        if (comment_pos != NULL)
                *comment_pos = '\0';

        return cmd;
}

void p_int(int number)
{
        char buf[20];
        int i = 0;

        if (number < 0)
        {
                buf[i++] = '-';
                number = -number;
        }
        do
        {
                buf[i++] = number % 10 + '0';
                number /= 10;
        }
        while (number > 0);

        while (i > 0)
        {
                write(STDOUT_FILENO, &buf[--i], 1);
        }
}
void my_print(const char *message)
{
        write(STDOUT_FILENO, message, strlen(message));
}

int redirect_number(char *cmd)
{
        char *token;
        token = _strtok(cmd, " ");
        while (token != NULL)
        {
                if (strcmp(token, ">") == 0)
                {
                        free(cmd); // edited
                        return 1;
                }
                else if (strcmp(token, ">>") == 0)
                {
                        free(cmd); // edited
                        return 2;
                }
                token = _strtok(NULL, " ");
        }
        free(cmd); // edited
        return 0;
}

char *output_name(char *cmd_copy)
{
        char *token;
        char *file_name = NULL;
        token = _strtok(cmd_copy, " ");
        while (token != NULL)
        {
                if ((strcmp(token, ">") == 0) || (strcmp(token, ">>") == 0))
                {
                        token = _strtok(NULL, " ");

                        if (token != NULL)
                        {
                                file_name = strndup(token, strlen(token));
                        }
                        token = NULL;
                        return file_name;
                }
                token = _strtok(NULL, " ");
        }
        return NULL;
}
char *_strtok(char *cmd, const char *delim)
{
        static char *last_token = NULL;
        char *token;
        char *delim_pos;

        if (cmd != NULL)
                last_token = cmd;

        if (last_token == NULL)
                return NULL;

        token = last_token;
        delim_pos = strpbrk(last_token, delim);
        if (delim_pos != NULL)
        {
                *delim_pos = '\0';
                last_token = delim_pos + 1;
        }
        else
        {
                last_token = NULL;
        }

        return token;
}
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
        char *buffer = *lineptr;
        size_t size = *n;
        size_t i = 0;
        int c;

        if (buffer == NULL || size == 0)
        {
                size = 128;
                buffer = malloc(size);
                if (buffer == NULL)
                return -1;
        }

        while (1)
        {
                c = getc(stream);
                if (c == EOF)
                {
                        if (i == 0)
                                return -1;
                        else
                                break;
                }

                if (i >= size - 1)
                {
                        size *= 2;
                        char *new_buffer = realloc(buffer, size);
                        if (new_buffer == NULL)
                                return -1;
                        buffer = new_buffer;
                }

                buffer[i++] = c;
                if (c == '\n')
                        break;
        }

        buffer[i] = '\0';
        *lineptr = buffer;
        *n = size;
        return i;
}
