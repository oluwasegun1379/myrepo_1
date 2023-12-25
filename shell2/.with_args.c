#include "shell.h"
/**
 * with_arg - Execute commands with arguments.
 * @line: Pointer to the command line inputs.
 *
 * Return: Nothing.
 */
void with_arg(char *line)
{
	int status;

	if (_strchr(line, '/') != NULL)
	{
		status = system(line);  // Execute the command using system
		if (status == -1)
		{
			printf("./shell: No such file or directory\n");  // Handle command not found error
		}
	}
}
