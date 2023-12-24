#include "shell.h"
/**
 * line_interpreter - Reads user input.
 * Description: Executes commands using system and
 * prints an error message if the command is not found
 *
 * Return: Nothing.
 */
void line_interpreter(void)
{
       	char *line = NULL;
	size_t len = 0;
	ssize_t read;

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
			if (strchr(line, '/') != NULL && strchr(line, ' ') == NULL)
			{
				int status = system(line); // Execute the command using system
				if (status == -1)
				{
					printf("./shell: No such file or directory\n"); // Handle command not found error
				}
			}
			else
			{
				with_arg(line);
			}
		}
	}
}
