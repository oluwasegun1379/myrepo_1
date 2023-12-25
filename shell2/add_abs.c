#include "shell.h"

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
		printf("%s: Command not found\n", cmd);
                free(path_copy);
		exit(1);
	}
        else
        {
                return cmd;
        }
}
