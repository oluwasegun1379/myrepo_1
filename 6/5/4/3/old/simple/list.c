#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
int main(int argc, char *argv[])
{
	char ls[5] = "ls";
	char pwd[5] = "pwd";
	char exit[5] = "exit";
	char echo[5] = "echo";
	char cmd[1024];
	char s[1024];
start3:
start2:
start1:
start:
	printf("$ ");
	scanf("%s", cmd);
	while(1)
	{
	if (strcmp(ls, cmd) == 0)
	{
		system("ls");
		goto start;
	}
	else if (strcmp(pwd, cmd) == 0)
	{
		system("pwd");
		goto start2;
	}
	else if (strcmp(echo, cmd) == 0)
	{
		system("echo argv[1]");
		goto start3;
	}
	else if (strcmp(exit, cmd) == 0)
	{
		return (0);
	}
	else
	{
		dprintf(1,"Error, %s is not a command!\n", cmd);
		goto start1;
	}
	}
	return (0);
}
