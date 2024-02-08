#include <stdlib.h>
#include <stdio.h>
int main()
{
	char *path = getenv("PATH");
	printf("PATH: %s\n", path);
	return (0);
}
