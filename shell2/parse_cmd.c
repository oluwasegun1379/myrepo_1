#include "shell.h"
/**
 * parse_cmd - Parse a command string into arguments.
 * @cmd: The input command string.
 *
 * Return: The number of arguments parsed.
 */
char **parse_cmd(char *cmd)
{
	char *token = NULL;
	int i = 0;
	char **argv = NULL;

	if (cmd == NULL)
	{
		return NULL;
	}

	int token_count = 0;
	char *tmp = strdup(cmd);
	token = _strtok(tmp, " ");
	while (token != NULL)
	{
		token_count++;
		token = _strtok(NULL, " ");
	}
	free(tmp);

	argv = calloc(token_count + 1, sizeof(char *));
	if (argv == NULL)
	{
		free(cmd);
		return (NULL);
	}

	token_count = 0;
	token = _strtok(cmd, " ");
	while (token != NULL)
	{
		argv[i] = strdup(token);
		if (argv[i] == NULL)
		{
			for (int j = 0; j < i; j++)
			{
				free(argv[j]);
			}
			free(argv);
			free(cmd);
			return (NULL);
		}
		i++;
		token = _strtok(NULL, " ");
	}
	argv[i] = NULL;
	free(cmd);

	return (argv);
}
