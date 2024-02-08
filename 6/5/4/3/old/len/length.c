#include<stdio.h>
int main()
{
	const char *str;
	str = "What is your name";
	int length = 0;
	while (*str++){
		length++;
	}
	printf("%d", length);
	return (0);
}
