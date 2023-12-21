#include "shell.h"

int main(void)
{
	char str[] = "This is an array of strings";
	char *stc;
	const char *delim = " ";
	int i, len = strlen(str);
	char *truncks;

	stc = malloc(sizeof(char *) * len);
	strcpy(stc, str);
	truncks = _strtok(stc, delim);
	for (i = 0; truncks != NULL; i++)
	{
		printf("%s\n", truncks);
		free(truncks);
		truncks = _strtok(NULL, delim);
	}
	printf("%s\n", str);
	free(stc);

	return (0);
}
