#include "shell.h"

/**
 **_cpstring - make a copy of a string
 *@destination: the destination string to be copied to
 *@strings: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_cpstring(char *destination, char *strings, int n)
{
	int i, j;
	char *s = destination;

	i = 0;
	while (strings[i] != '\0' && i < n - 1)
	{
		destination[i] = strings[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@destination: the first string
 *@strings: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *destination, char *src, int n)
{
	int i, j;
	char *s = destination;

	i = 0;
	j = 0;
	while (destination[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		destination[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		destination[i] = '\0';
	return (s);
}

/**
 **chastr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *chastr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
