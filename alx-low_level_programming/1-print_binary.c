#include "main.h"
#include <stdio.h>
/**
 * print_binary - unction that prints d binary representation of a number.
 * @n: Integer to be converted to binary.
 *
 * Return: Nothing.
 */
void print_binary(unsigned long int n)
{
	if (n > 1)
		print_binary(n >> 1);
	putchar((n & 1) ? '1' : '0');
}
