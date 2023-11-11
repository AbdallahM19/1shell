#include "shell.h"

int _putchar(char cat)
{
    static int count;
    static char BUF[BUF_Wr_ON];

    if (cat == BUF_FLUSH || count >= BUF_Wr_ON)
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
    while (*argv != '\0')
    {
        _putchar(*argv);
        argv++;
    }
}

char *_strdup(const char *str)
{
    int i;
    char *p;
    int length = _strlength(str);

    if (str == NULL)
        return (NULL);
    p = malloc((length + 1) * sizeof(char));
    if (p == NULL)
        return (NULL);
    for (i = 0; i < length; i++)
        p[i] = str[i];
    p[i] = '\0';
    return (p);
}

char *_strcpy(char *cat, char *kitty)
{
    int x = 0;

    if (cat == kitty || kitty == NULL)
        return (cat);
    while (kitty[x] != '\0')
    {
        cat[x] = kitty[x];
        x++;
    }
    cat[x] = '\0';
    return (cat);
}
