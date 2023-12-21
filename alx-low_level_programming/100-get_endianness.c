#include "main.h"
/**
 * get_endianness - function that checks the endianness.
 *
 * Return: 0 if big endian, 1 if little endian.
 */
int get_endianness(void)
{
	int num = 1;
	char *ptrToNum = (char *)&num;

	/* If the first byte of the integer is non-zero, */
	/* the system is little endian */
	if (*ptrToNum)
		return (1);  /* little endian */
	else
		return (0);  /* big endian */
}
