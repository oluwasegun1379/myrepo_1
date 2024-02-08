#include "shell.h"
void print_env(void)
{
	char **allenv = environ;

	while (*allenv != NULL)
	{
		printf("%s\n", *allenv);
		allenv++;
	}
}

