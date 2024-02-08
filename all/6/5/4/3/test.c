#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define bufsize 100
#define argscount 10 
void readcmd(char *cmd)
{
	printf("segun/shell~> ");
	fgets(cmd, bufsize, stdin);
	int len = strlen(cmd);
	if (cmd[len - 1] == '\n')
		cmd[len - 1] = '\0';
}
void parsecmd(char *cmd, char **argv)
{
	char *input;
	int i = 0;

	input = strtok(cmd, " ");
	while (input != NULL && i < argscount)
	{
		argv[i] = input;
		input = strtok(NULL, " ");
		i++;
	}
	argv[i] = NULL;
}
void executecmd(char **argv)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(argv[0], argv) == -1)
			perror("Shell");
		exit (EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		do{
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	else
		perror("Shell");
}
int main(void)
{
	char cmd[bufsize];
	char *argv[argscount];

	while (1)
	{
		readcmd(cmd);
		if (strcmp(cmd, "exit") == 0)
			break;
		else if (cmd[0] == '#')
		{
			continue;
		}
		else
		{
			parsecmd(cmd, argv);
			if (strcmp(argv[0], "cd") == 0)
			{
				if (argv[1] == NULL)
					printf("Expect an argument after \"cd\" \n");
				else
					if (chdir(argv[1]) != 0)
					{
							perror("Shell");
					}
			}
			else
				executecmd(argv);
		}
	}
	return (0);
}
