#include "main.h"
#include <string.h>
/**
 * binary_to_uint - function that converts a
 * binary number to an unsigned int.
 * @b: Pointer to a string of 0 or 1.
 *
 * Return: the converted number, or 0 if
 * there is one or more chars in the string b that is not 0 or 1
 * if b is NULL.
 */
unsigned int binary_to_uint(const char *b)
{
	size_t i = 0;
	size_t sum = 0;

	if (b == NULL)
		return (0);
	for (i = 0; b[i] != '\0'; i++)
	{
		if (b[i] != '0' && b[i] != '1')
			return (0);
		sum = sum * 2 + (b[i] - '0');
	}
	return (sum);
}
