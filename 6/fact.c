#include <stdio.h>
int fun(int x)
{
	if (x <= 1)
		return (1);
	else
		return (x * fun(x - 1));
}
int main()
{
	printf("The answer is : %d\n", fun(4));
	return (0);
}

