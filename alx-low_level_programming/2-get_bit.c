#include "main.h"
#include <stdlib.h>
/**
 * get_bit - function that returns the value of a bit at a given index.
 * @n: Unsigned decimal number.
 * @index: Position of the value to be returned.
 *
 * Return: value of the bit at index index or -1 if an error occured.
 */
int get_bit(unsigned long int n, unsigned int index)
{
	if (index >= (sizeof(unsigned long int) * 8))
		return (-1);
	return ((n >> index) & 1);
}
