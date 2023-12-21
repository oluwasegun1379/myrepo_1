#include "main.h"
/**
 * clear_bit - function that sets the value of a bit to 0 at a given index.
 * @n: Unsigned integer.
 * @index: Position at which the bit will be invert to 0;
 *
 * Return: 1 if it worked, or -1 if an error occurred.
 */
int clear_bit(unsigned long int *n, unsigned int index)
{
	unsigned long int mask;

	if (index >= (sizeof(unsigned long int) * 8))
		return (-1);

	mask = ~(1ul << index);
	*n = (*n) & mask;
	return (1);
}
