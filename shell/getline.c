#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *buf = NULL;
	size_t n = 10;

	buf = malloc(sizeof(char) * n);
	if (buf == NULL)
	{
		return (1);
	}
	printf("$ ");
	getline(&buf, &n, stdin);
	printf("%s", buf);
	printf("%ld\n", n);

	free(buf);
	return (0);
}


