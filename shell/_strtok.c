#include "shell.h"
char *_strtok(char *string, const char *delimeter)
{
	static char *lastToken = NULL;
	int i, j;

	if (string == NULL)
	string = lastToken;

	if (string == NULL)
	return (NULL);

	int len = strlen(string);
	char *word = malloc(sizeof(char) * (len + 1));

	if (word == NULL)
	return (NULL);

	for (i = 0, j = 0; i <= len; i++)
	{
	if (string[i] == '\0' || _strchr(delimeter, string[i]) != NULL)
	{
	word[i] = '\0';
	if (j > 0)
	{
	lastToken = &string[i + 1];
	char *result = strdup(word);
	free(word);
	return (result);
	}
	}
	else
	{
	word[j] = string[i];
	j++;
	}
	}
	free(word);
	return (NULL);
}
