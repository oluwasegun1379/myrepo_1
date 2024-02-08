#include <stdio.h>
#include <stdlib.h>
int main()
{
	char *line;
	size_t n = 0;
	getline(&line, &n, stdin);
	line = malloc(sizeof(char) * 10);
	printf("%s", line);
	return (0);
}
