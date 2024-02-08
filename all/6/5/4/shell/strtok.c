#include "shell.h"
#include <stdbool.h> // For bool type

char* my_strtok(char* str, const char* delimiters)
{
    static char* nextToken = NULL;
    char* tokenStart;
    bool delimiterFound = false;

    if (str != NULL)
    {
        nextToken = str;
    }
    else if (nextToken == NULL)
    {
        return NULL;
    }

    // Skip leading delimiters
    while (*nextToken && strchr(delimiters, *nextToken))
    {
        nextToken++;
    }

    if (*nextToken == '\0')
    {
        nextToken = NULL;
        return NULL;
    }

    tokenStart = nextToken;

    // Find the end of the token
    while (*nextToken && !strchr(delimiters, *nextToken))
    {
        nextToken++;
    }

    if (*nextToken)
    {
        *nextToken = '\0';
        nextToken++;
    }
    else
    {
        nextToken = NULL;
    }

    return tokenStart;
}

