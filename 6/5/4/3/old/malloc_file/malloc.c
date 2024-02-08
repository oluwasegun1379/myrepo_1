#include <stdio.h>
#include <stdlib.h>
void *_malloc(char *str)
{
	int i, len;
	char *s;
	int n = 1;

	len = strlen(str);
	s = malloc(sizeof(char) * n);
	if (s == NULL)
	{
		return (NULL);
	}
	for (i = 0; i < n; i++)
		s[i] = str[i];

	int m = n + 1;
	s = realloc(s, sizeof(char) * m);
	for (i = 0; i < m; i++)
		s[i] = str[i];

	s[i] = '\0';

	return (s);
}
int main(void)
{
	char *st;
	char *new_s;

	st = "school captain";
	new_s = _malloc(st);
	printf("%s\n", new_s);
	free(new_s);
	return (0);
}
