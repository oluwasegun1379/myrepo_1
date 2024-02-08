#include <stdlib.h>
#include <stdio.h>

extern char **environ;

int main()
{
	char **env = environ;
	while (env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
	putchar('\n');
	return (0);
}
