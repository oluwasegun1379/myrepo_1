#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *_strtok(char *string, const char *delimiter)
{
    static char *lastToken = NULL; // Keep track of the last token
    int i, j;
    
    if (string == NULL)
        string = lastToken;
    
    if (string == NULL)
        return NULL;

    int len = strlen(string);
    char *word = malloc(sizeof(char) * (len + 1));

    for (i = 0, j = 0; i <= len; i++)
    {
        if (string[i] == '\0' || strchr(delimiter, string[i]) != NULL)
        {
            word[j] = '\0';
            if (j > 0)
            {
                lastToken = &string[i + 1]; // Update lastToken for the next call
                return word;
            }
        }
        else
        {
            word[j] = string[i];
            j++;
        }
    }

    free(word); // Free allocated memory if no token found
    return NULL;
}

int main(void)
{
    char str[] = "This is an array of strings";
    char *stc = malloc(sizeof(char) * strlen(str));
    const char *delim = " ";
    int i;
    char *trunks;

    strcpy(stc, str);
    trunks = strtok(stc, delim);
    for (i = 0; trunks != NULL; i++)
    {
        printf("%s\n", trunks);
        trunks = strtok(NULL, delim);
    }
    printf("%s\n", str);
    free(stc);

    char *text = _strtok("hello world", " ");
	printf("%s\n", text);

    return 0;
}

