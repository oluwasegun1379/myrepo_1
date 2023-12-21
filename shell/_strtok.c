#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char *_strtok(char *string, const char delimeter)
{
	int len = strlen(string);
	char strc[len + 1];
	int i, j;

	for (i = 0; i <= len; i++)
	{
		if (string[i] != delimeter)
		{
			strc[i] = string[i];
		}
		strc[i++] = '\0';
	}
	printf("%s\n", strc);
}

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
	_strtok("hello world", " ");
	return (0);
}
