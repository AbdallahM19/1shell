#include "shell.h"

int _putchar(char cat)
{
	static int count;
	static char BUF[BUF_Wr_ON];

	if (cat == NEGATIVE || count >= BUF_Wr_ON)
	{
		write(1, BUF, count);
		count = 0;
	}
	if (cat != BUF_FLUSH)
		BUF[count++] = cat;
	return (1);
}

void _puts(char *argv)
{
	int x;

	for (x = 0; argv[x] != '\0'; x++)
		_putchar(argv[x]);
}

char *_strdup( const char *str) /*dublicate a string*/
{
	int i;
	char *p;
	int length = strlen(str);

	if (str == NULL)
		return (NULL);
	p = malloc(length + 1 * sizeof(char));
	if (p == 0)
		return (NULL);
	for (i = 0; i < length; i++)
		p[i] = str[i];
	return (p);
}

char *_strcpy(char *cat, char *kitty)
{
	int x = 0;

	if (cat == kitty || kitty == 0)
		return (cat);
	for (; kitty[x] != '\0'; x++)
		cat[x] = kitty[x];
	cat[x] = '\0';
	return (cat);
}
