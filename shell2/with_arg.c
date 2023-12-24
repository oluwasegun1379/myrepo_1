#include "shell.h"
/**
 * with_arg - Execute commands with arguments.
 * Description: Execute the command with arguments using the system function
 * and print an error message if the command is not found.
 * @line: Pointer to the command line inputs.
 *
 * Return: Always 0.
 */
void with_arg(char *line)
{
	if (strchr(line, '/') != NULL)
	{
		int status = system(line);  // Execute the command using system
		if (status == -1)
		{
			printf("./shell: No such file or directory\n");  // Handle command not found error
		}
	}
	else
	{
		printf("./shell: No such file or directory\n");
	}
}

