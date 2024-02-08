#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	int i;
	int *ptr;

	
	ptr = malloc(sizeof(int) *99);
	for (i = 1; i <= 99; i++)
	{
		ptr[i] = i;
		printf("%d", ptr[i]);
		if (i % 10)
		{
			putchar(' ');
		}
		else
		{
			putchar('\n');
		}
	}
	putchar('\n');
	free(ptr);
	return (0);
}
