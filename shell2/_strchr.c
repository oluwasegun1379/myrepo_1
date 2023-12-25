#include "shell.h"
/** strchr - Locate the first occurrence of a character in a string.
 * @s: The string to search.
 * @c: The character to locate.
 *
 * Return: A pointer to the first occurrence of the character @c in the string
 * @s, or NULL if the character is not found.
 */
char *_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return (char *)s;
		s++;
	}

	if (*s == c)
		return (char *)s;

	return (NULL);
}
