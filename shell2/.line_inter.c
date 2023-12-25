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
			// printf("\n");
			free(line);
			break; // Handle end of file (Ctrl+D)
		}
		else
		{
			line[read - 1] = '\0'; // Remove trailing newline

			// Check if the command includes a path and has no arguments
			if (_strchr(line, '/') != NULL && _strchr(line, ' ') == NULL)
			{
				status = system(line); // Execute the command using system
				if (status == -1)
				{
					printf("./shell: No such file or directory\n"); // Handle command not found error
				}
			}
			else if (_strchr(line, '/') == NULL)
			{
				argv = parse_cmd(line);
				execute_cmd(argv);
				free(argv);
			}
			else
			{
				with_arg(line);
			}
		}
	}
}
