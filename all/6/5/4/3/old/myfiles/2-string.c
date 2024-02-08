#include <stdio.h>
int main()
{
	char *ch ="who is in the garden";
	int i=0;
	while (ch[i] != '\0')
	{
	printf("%c", ch[i]);
	i++;
	}
	printf("\n%d\n", i);
	int c;
	for (c=i; c>=0; c--)
	{
	printf("%c", ch[i]);
	i--;
	}
return (0);
}
