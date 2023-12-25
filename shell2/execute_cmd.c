#include "shell.h"
/**
 * execute_cmd - Execute a command and handle errors.
 * @argv: Arrays of command and its arguments.
 *
 * Return: 0 on successful execution, -1 on failure.
 */
int execute_cmd(char **argv)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			perror("execve");	
			printf("argv[0] = %s\n", argv[0]);
			exit(1);
		}
	}
	else if (pid > 0)
	{
		pid_t child_pid = waitpid(pid, &status, 0);
		if (child_pid == -1)
		{
			perror("waitpid");
			exit(1);
		}
		return (0);
	}
	else
	{
		perror("fork failed");
		exit(1);
	}

	return (-1);
}
