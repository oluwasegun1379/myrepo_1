#include "shell.h"
/**
 * _strtok - Tokenize a string based on a given set of delimiters.
 * @string: The string to be tokenized.
 * @delimiter: The set of delimiters used for tokenization.
 *
 * Return: A pointer to the next token found in the string, or
 * if no more tokens are found.
 */
char *_strtok(char *string, const char *delimeter)
{
	static char *lastToken = NULL;
	char *tokenStart;

	if (string != NULL)
	{
		lastToken = string;
	}

	if (lastToken == NULL || *lastToken == '\0')
	{
		return NULL;
	}

	tokenStart = lastToken + strspn(lastToken, delimeter);

	if (*tokenStart == '\0')
	{
		lastToken = NULL;
		return NULL;
	}

	lastToken = tokenStart + strcspn(tokenStart, delimeter);

	if (*lastToken != '\0')
	{
		*lastToken = '\0';
		lastToken++;
	}
	else
	{
		lastToken = NULL;
	}

	return tokenStart;
}
