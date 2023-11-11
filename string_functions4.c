#include "shell.h"

int _strspn(const char *str, const char *accept)
{
    int i, j;

    for (i = 0; str[i] != '\0'; i++)
    {
        for (j = 0; accept[j] != '\0'; j++)
        {
            if (str[i] == accept[j])
                break;
        }
        if (accept[j] == '\0')
            return i;
    }
    return i;
}

char *_strpbrk(char *str, const char *accept)
{
    int i, j;
    for (i = 0; str[i] != '\0'; i++)
    {
        for (j = 0; accept[j] != '\0'; j++)
        {
            if (str[i] == accept[j])
                return &str[i];
        }
    }
    return NULL;
}

char *strtok_custom(char *str, const char *delimiters)
{
    static char *next_token = NULL;

    if (str != NULL)
    {
        next_token = str;
    }
    else if (next_token == NULL)
    {
        return (NULL);
    }
    next_token += _strspn(next_token, delimiters);
    if (*next_token == '\0')
    {
        next_token = NULL;
        return (NULL);
    }
    char *token = next_token;
    next_token = _strpbrk(next_token, delimiters);
    if (next_token != NULL)
    {
        *next_token = '\0';
        next_token++;
    }
    return (token);
}
