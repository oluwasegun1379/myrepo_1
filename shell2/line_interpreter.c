#include "shell.h"
/**
 * line_interpreter - Reads user input and executes commands.
 */
void line_interpreter(void)
{
       	char *line = NULL;
	char **argv;
	size_t len = 0;
	ssize_t read;
	int status;

	while (1)
	{
		printf("#cisfun$ ");
		if ((read = getline(&line, &len, stdin)) == -1)
		{
			if (line != NULL)
				free(line);
			break; // Handle end of file (Ctrl+D)
		}
		else
		{
			line[read - 1] = '\0';
			
			line = add_abs_path_to_cmd(line);
			argv = parse_cmd(line);
			execute_cmd(argv);

			for (int i = 0; argv[i] != NULL; i++)
			{
				free(argv[i]);
			}
			free(argv);
		}
	}
	if (line != NULL)
		free(line);
	if (argv != NULL)
		free(argv);
}
