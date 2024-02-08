#include "main.h"
#include <stdio.h>

void _puts(char *str)
{
	size_t length=0;
	int i;
	while (*str != '\0')
	{
		_putchar(*str);
		str++;
		length++;
	}
	_putchar('\n');
	_putchar('length');
	_putchar('\n');
}
