#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * simple_print_buffer - prints buffer in hexa.
 * @beffer: the address of memory to print
 * @size: the size of the memory to print
 * Return: Nothing.
 */
void simple_print_buffer(char *buffer, unsigned int size)
{
	unsigned int i;

	i = 0;
	while (i < size)
	{
		if (i % 10)
		{
			printf(" ");
		}
		if (!(i % 10) && i)
		{
			printf("\n");
		}
		printf("0x%02d", buffer[i]);
		i++;
	}
	printf("\n");
}
void *_calloc(unsigned int nmemb, unsigned int size)
{
	int i;
	int *ptr;

	if (nmemb == 0 || size == 0)
	{
		return (NULL);
	}
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
	{
		return (NULL);
	}
	for (i = 0; i < nmemb; i++)
	{
		ptr[i] = 0;
	}
	ptr[i] = '\0';
	return (ptr);
}
int main(void)
{
	char *a;

	a = _calloc(98, sizeof(char));
	strcpy(a, "Best");
	strcpy(a + 4, "school! :)\n");
	a[97] = '!';
	simple_print_buffer(a, 98);
	free(a);
	return (0);
}

