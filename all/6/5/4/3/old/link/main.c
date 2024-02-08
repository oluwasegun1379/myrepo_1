#include <stdio.h>
#include <stdlib.h>
int main()
{
	int *ptr = malloc(sizeof(int));
	*ptr = 356;
	printf("The value ptr is pointing to is --> %d\n", *ptr);

	return (0);
}
