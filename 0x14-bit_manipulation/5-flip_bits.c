#include "main.h"
/**
 * flip_bits - function that returns the number of bits you
 * would need to flip to get from one number to another.
 * @n: Unsigned Integer to be flib using bit.
 * @m: Unsigned integer to flip to.
 *
 * Return: flipped value on SUCCESS.
 */
unsigned int flip_bits(unsigned long int n, unsigned long int m)
{
	/* XOR the two numbers to get the bits that differ */
	unsigned long int dif = n ^ m;
	unsigned int count = 0;

	/* Count the number of set bits (1s) in the XORed */
	/* number using bit-shifting */
	while (dif != 0)
	{
		count += dif & 1;
		dif >>= 1;
	}
	return (count);
}
