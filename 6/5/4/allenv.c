#include <stdio.h>
#include <stdlib.h>
extern char **environ;
int main()
{
	char **allenv = environ;
	while (*allenv != NULL)
	{
		printf("%s", *allenv);
		allenv++;
	}
	return (0);
}
