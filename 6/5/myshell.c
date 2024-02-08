#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_CMD_LENGTH 1024
#define MAX_ARGS 256

typedef struct {
    char cmd[MAX_CMD_LENGTH];
    char cmd_copy[MAX_CMD_LENGTH];
    char *arg[MAX_ARGS];
    char output_file[MAX_CMD_LENGTH];
    char cmd_path[MAX_CMD_LENGTH];
    char *token;
    char **allenv;
    char *path;
    char *dir;
    char *pathcopy;
    int index;
    int redirect_num;
    pid_t pid;
    int status;
    int i;
    int j;
} var_t;

void parse_args(var_t *var) {
    var->index = 0;
    var->token = strtok(var->cmd, " ");

    while (var->token != NULL) {
        if (strcmp(var->token, ">") == 0) {
            var->redirect_num = 1;
            var->token = strtok(NULL, " ");
            if (var->token != NULL)
                strcpy(var->output_file, var->token);
            var->token = NULL;
        } else if (strcmp(var->token, ">>") == 0) {
            var->redirect_num = 2;
            var->token = strtok(NULL, " ");
            if (var->token != NULL)
                strcpy(var->output_file, var->token);
            var->token = NULL;
        }
        var->arg[var->index] = var->token;
        var->token = strtok(NULL, " ");
        var->index++;
    }

    var->arg[var->index] = NULL; // Set the last element to NULL
}

void execute_args(var_t *var) {
    var->pid = fork();

    if (var->pid == 0) {
        if (var->redirect_num == 1) {
            freopen(var->output_file, "w", stdout);
        } else if (var->redirect_num == 2) {
            freopen(var->output_file, "a", stdout);
        }
        fflush(stdout);

        execvp(var->arg[0], var->arg); // Pass the arg array directly to execvp

        // execvp only returns if there's an error
        perror("execvp");
        exit(EXIT_FAILURE);
    } else if (var->pid > 0) {
        waitpid(var->pid, &var->status, 0);
    } else {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
}

void print_env() {
    var_t var;
    var.allenv = environ;

    while (*var.allenv != NULL) {
        printf("%s\n", *var.allenv);
        var.allenv++;
    }
}

int cmd_exist(var_t *var) {
    var->path = getenv("PATH");
    var->dir = strdup(var->path);

    var->pathcopy = strtok(var->dir, ":");

    while (var->pathcopy != NULL) {
        strcpy(var->cmd_path, var->pathcopy);
        strcat(var->cmd_path, "/");
        strcat(var->cmd_path, var->cmd);

        if (access(var->cmd_path, X_OK) == 0) {
            free(var->dir);
            return 1;
        }

        var->pathcopy = strtok(NULL, ":");
    }

    free(var->dir);
    return 0;
}

void skip_space(var_t *var) {
    while (var->cmd[var->i] == ' ') {
        var->i++;
    }

    var->j = var->i;

    while (var->cmd[var->j] != '\0') {
        var->cmd[var->i] = var->cmd[var->j];
        var->i++;
        var->j++;
    }

    var->cmd[var->i] = '\0';
}

void clear_cmd(var_t *var) {
    memset(var->cmd, 0, sizeof(var->cmd));
    memset(var->cmd_copy, 0, sizeof(var->cmd_copy));
    memset(var->output_file, 0, sizeof(var->output_file));
    memset(var->cmd_path, 0, sizeof(var->cmd_path));

    for (int i = 0; i < MAX_ARGS; i++) {
        var->arg[i] = NULL;
    }

    var->index = 0;
    var->redirect_num = 0;
    var->pid = 0;
    var->status = 0;
    var->i = 0;
    var->j = 0;
    var->token = NULL;
}

int main() {
    var_t var;

    while (1) {
        printf("OLUWASEGUN-BASH-SHELL~# ");
        fflush(stdout);

        ssize_t line_size;
        char *line = NULL;
        size_t len = 0;

        line_size = getline(&line, &len, stdin);
        if (line_size == -1) {
            free(line);
            break;
        }

        strcpy(var.cmd, line);
        free(line);

        if (var.cmd[strlen(var.cmd) - 1] == '\n') {
            var.cmd[strlen(var.cmd) - 1] = '\0';
        }

        skip_space(&var);

        if (strcmp(var.cmd, "exit") == 0) {
            break;
        } else if (strcmp(var.cmd, "printenv") == 0) {
            print_env();
        } else {
            clear_cmd(&var);

            if (cmd_exist(&var)) {
                parse_args(&var);
                execute_args(&var);
            } else {
                printf("Command not found: %s\n", var.cmd);
            }
        }
    }

    return 0;
}

