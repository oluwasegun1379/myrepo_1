#include <stdio.h>
/**
 * main - print the result of palindrome string
 *
 * Return: 0
 */
int _palindrome(char *s);
int _strlen(char *s);
int _check_palindrome(char *s, int start, int end);
int main(void)
{
	int p;

	p = _palindrome("level");
	printf("%d\n", p);

	p = _palindrome("test");
	printf("%d\n", p);

	p = _palindrome("step on no pets");
	printf("%d\n", p);

	return (0);
}




int _palindrome(char *s)
{
	int l = _strlen(s);

	if (l == 0 || l == 1)
	{
		return (1);
	}

	return (_check_palindrome(s, 0, l - 1));
}




int _strlen(char *s)
{
	if (*s == '\0')
	{
		return (0);
	}

	return (1 + _strlen(s + 1));
}




int _check_palindrome(char *s, int start, int end)
{
	if (start >= end)
	{
		return (1);
	}
	
	if (*(s + start) == *(s + end))
	{
		return (_check_palindrome(s, start + 1, end -1));
	}

	return (0);
}
