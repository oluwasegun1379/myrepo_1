#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	char str[] = "This is an array of strings";
	char *stc = malloc(sizeof(char *) * strlen(str));
	const char *delim = " ";
	int i;
	char *truncks;

	strcpy(stc, str);
	truncks = strtok(stc, delim);
	for (i = 0; truncks != NULL; i++)
	{
		printf("%s\n", truncks);
		truncks = strtok(NULL, delim);
	}
	printf("%s\n", str);
	free(stc);

	return (0);
}
