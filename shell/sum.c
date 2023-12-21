#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
	int i;
	int sum = 0;

	for (i = 0; i < ac; i++)
	{
		sum += atoi(av[i]);
	}
	printf("sum = %d\n", sum);
	printf("ac = %d\n", sum);
	for (i = 0; i < ac; i++)
		printf("av[%d] = %s\n", i, av[i]);

	return (0);
}

