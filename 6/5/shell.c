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

typedef struct {
    int redirect_num;
    char output_file_name[ARG_COUNT];
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

int main(void) {
    int previousExitStatus = 0;
    int exitStatus;
    char *cmd = NULL;
    char *cmd_copy = NULL;
    char **argv;
    size_t n = 0;
    ssize_t len;

    while (1) {
        my_print("new~shell$ ");
        if ((len = getline(&cmd, &n, stdin)) != -1) {
            if (cmd[len - 1] == '\n')
                cmd[len - 1] = '\0';

            cmd_copy = strdup(cmd);

            if (strlen(cmd) == 0) {
                continue;
            }

            cmd = remove_comment(cmd);
            argv = parse_cmd(cmd);

            if ((strcmp(argv[0], "echo") == 0) && (strcmp(argv[1], "$?") == 0)) {
                p_int(previousExitStatus);
                my_print("\n");
                continue;
            }

            if (argv[0] != NULL) {
                if (strcmp(argv[0], "exit") == 0) {
                    break; // EOD
                }

                if (builtin(argv) == 1) {
                    exitStatus = execute_cmd(argv, cmd_copy);
                    previousExitStatus = exitStatus;
                }
            }
        } else {
            break;
        }
    }

    free(cmd);
    free(cmd_copy);
    my_print("logout\n");
    exit(EXIT_SUCCESS);
}

char **parse_cmd(char *cmd) {
    char *token;
    int i = 0;
    char **argv = malloc(sizeof(char *) * (ARG_COUNT + 1));
    if (cmd == NULL || argv == NULL)
        return NULL;

    token = strtok(cmd, " ");
    while (token != NULL && i < ARG_COUNT) {
        argv[i] = strdup(token);
        i++;
        token = strtok(NULL, " ");
    }
    argv[i] = NULL;
    return argv;
}

int execute_cmd(char **argv, char *cmd) {
    int status;
    pid_t pid;
    int redirect_n;
    char *cmd_copy = strdup(cmd);
    char *file_name;

    pid = fork();
    if (pid == 0) {
        argv[0] = add_abs_path_to_cmd(argv[0]);

        redirect_n = redirect_number(cmd);

        file_name = output_name(cmd_copy);

        if (redirect_n == 1) {
            freopen(file_name, "w", stdout);
        } else if (redirect_n == 2) {
            freopen(file_name, "a", stdout);
        }
        fflush(stdout);

        if (execve(argv[0], argv, environ) == -1) {
            perror("execve");
            exit(1);
        }
    } else if (pid > 0) {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            free(argv);
            free(cmd_copy);
            return WEXITSTATUS(status);
        }
    } else {
        perror("fork failed");
        free(argv);
        free(cmd_copy);
        exit(1);
    }

    free(argv);
    free(cmd_copy);
    return -1;
}

char *add_abs_path_to_cmd(char *cmd) {
    char *path = getenv("PATH");
    char *path_copy;
    char *full_path;
    char *dir;
    char *token;

    if (strchr(cmd, '/') == NULL) {
        path_copy = strdup(path);

        token = strtok(path_copy, ":");
        while (token != NULL) {
            full_path = malloc(strlen(token) + strlen(cmd) + 2);
            strcpy(full_path, token);
            strcat(full_path, "/");
            strcat(full_path, cmd);

            if (access(full_path, X_OK) == 0) {
                free(path_copy);
                return full_path;
            }

            free(full_path);
            token = strtok(NULL, ":");
        }

        my_print(cmd);
        my_print(": Command not found\n");
        free(path_copy);
        exit(1);
    } else {
        return cmd;
    }
}

int builtin(char **argv) {
    const char *homeDir;
    if (strcmp(argv[0], "cd") == 0) {
        if (argv[1] == NULL) {
            homeDir = getenv("HOME");
            if (chdir(homeDir) == -1)
                my_print("Fail to change to home directory\n");
        } else if (chdir(argv[1]) != 0) {
            perror("cd");
        }
        return 0;
    } else if (strcmp(argv[0], "env") == 0) {
        print_env();
        return 0;
    }

    return 1;
}

void print_env() {
    char **env = environ;
    while (*env != NULL) {
        my_print(*env);
        my_print("\n");
        env++;
    }
}

char *remove_comment(char *cmd) {
    char *comment_pos = strchr(cmd, '#');

    if (comment_pos != NULL)
        *comment_pos = '\0';

    return cmd;
}

void p_int(int number) {
    char buf[20];
    int i = 0;

    if (number < 0) {
        buf[i++] = '-';
        number = -number;
    }
    do {
        buf[i++] = number % 10 + '0';
        number /= 10;
    } while (number > 0);

    while (i > 0) {
        write(STDOUT_FILENO, &buf[--i], 1);
    }
}

void my_print(const char *message) {
    write(STDOUT_FILENO, message, strlen(message));
}

int redirect_number(char *cmd) {
    char *token;
    token = strtok(cmd, " ");
    while (token != NULL) {
        if (strcmp(token, ">") == 0) {
            return 1;
        } else if (strcmp(token, ">>") == 0) {
            return 2;
        }
        token = strtok(NULL, " ");
    }
    return 0;
}

char *output_name(char *cmd_copy) {
    char *token;
    char *file_name = NULL;
    token = strtok(cmd_copy, " ");
    while (token != NULL) {
        if ((strcmp(token, ">") == 0) || (strcmp(token, ">>") == 0)) {
            token = strtok(NULL, " ");

            if (token != NULL) {
                file_name = strdup(token);
            }
            token = NULL;
            return file_name;
        }
        token = strtok(NULL, " ");
    }
    return NULL;
}

