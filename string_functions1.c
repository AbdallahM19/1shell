#include "shell.h"

/**
 * _strlen - Write a function that returns the length of a string.
 * @s: string parameter input
 * Return: length string
 */
int _strlength(char *string)
{
	int count = 0;

	while (*string != '\0')
	{
		count++;
		string++;
	}
	return (count);
}

/**
 * _strcmp - a function that compares two strings
 * @s1: string 1 input to compare
 * @s2: against this other string 2
 * Return: 0 / postive / negative
*/

int _strcmp(char *s1, char *s2)
{
	int i;
	int result = 0;
/* use for loop*/
/*calculate the result to compare*/
	for (i = 0; s1[i] != '\0' && result == 0; i++)
	{
		result = s1[i] - s2[i];
	}
	return (result);
}

/**
 * start_with - chaecks if needle starts with haystack
 * @haystack: string to seach
 * @needle: substring to find
 * Return: address
*/
char *starts_with(const char *cat, const char *kitty)
{
	while (*kitty)
		if (*kitty++ != *cat++)
			return (NULL);
	return ((char *)cat);
}

/**
 * _strcat - Write a function that concatenates two strings.
 * @dest: pointer to destnation input
 * @src: pointer to source input
 * Return: pointer to resulting string @dest
 */
char *_strcat(char *dest, char *src)
{
	int i = 0, j = 0;

	while (dest[j] != '\0')
		j++;
	while (src[i] != '\0')
	{
		dest[j] = src[i];
		j++;
		i++;
	}
	dest[j] = '\0';
	return (dest);
}
