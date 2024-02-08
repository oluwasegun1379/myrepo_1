#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
int main(void)
{
	char str[1024];
	puts("Enter a string: ");
	fgets(str, 1024, stdin);
	if (*str == '\0')
		exit(0);
	int len = strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
	printf("%s\n", str);
	return (0);
}
