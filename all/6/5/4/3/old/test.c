#include <stdio.h>
#include <stdlib.h>
void add3(int a, int b, int c)
{
	printf("%d\n", a+b+c);
}
void add(int a, int b)
{
	printf("%d\n", a+b);
}

int main(void)
{
	int len;
	int i;
	float t = 5;
	size_t a = 5;
	unsigned int b = 10;
	printf("a: %d\n", a);
	printf("b: %d\n", b);
	printf("sizeof(i)= %d\n" , sizeof(i));
	//printf(".0d\n", 0);
	add3(5, 5, 5);
	add(5, 5);
	len = printf("HELLO WORLD\n");
	printf("len is %d\n", len);
	printf("%d\n", (O_WRONLY << 1));
	printf("5 after right shift = %f\n", (t >> 1));

	return (0);
}

