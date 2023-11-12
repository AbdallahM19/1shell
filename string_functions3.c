#include "shell.h"

char *_strncat(char *cat, char *kitty, int num)
{
	int i, j;

	for (i = 0; kitty[i] != '\0'; i++)
		;
	for (j = 0; cat[j] != 0 && j < num; j++)
	{
		kitty[i + j] = cat[j];
	}
	if (j < num)
		kitty[j] ='\0';
	return (kitty);
}

char *_strncpy(char *cat, char *kitty, int num)
{
	int x = 0, y = 0;

	for (; kitty[x] != '\0' && x < num-1; x++, y++)
		cat[y] = kitty[x];
	if (y < num)
	{
		for (; y < num; y++)
			cat[y] = '\0';
	}
	return (cat);
}

char *_strchr(char *p, char x)
{
	while (*p != '\0')
	{
		if (*p == x)
			return (p);
		p++;
	}
	return (NULL);
}
