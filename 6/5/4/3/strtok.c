#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define bufsize 1024
int main()
{
	int i = 0;
	char *token;

	char args[bufsize];
	fgets(args, bufsize, stdin);
	int len = strlen(args);
	if (args[len - 1] == '\n')
		args[len - 1] = '\0';

	token = strtok(args, " ");
	while(token != NULL)
		printf("%s ", token), token = strtok(NULL, " ");
	putchar('\n');

	return (0);
}
