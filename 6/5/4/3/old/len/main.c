#include <stdio.h>
#include "main.h"

int main(void)
{
	int a = 34;
	int b = 54;
	

	printf("Enter first number: ");
	scanf("%d\n", &a);

	printf("Enter second number: ");
	scanf("%d\n", &b);

	int x, y;

	x = add(a, b);
	y = sub(a, b);

	printf("addition of %d and %d is %d\n", a, b, x);
	printf("subtraction of %d and %d is %d\n", a, b, y);

	return (0);
}
