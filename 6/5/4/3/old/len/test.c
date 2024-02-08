#include <stdio.h>
#include <ctype.h>
int main(void)
{
	char *s1 = "5555 is there";
	int p;
	p = isalpha(*s1);
	printf("%d\n", p);

	return (0);
}

