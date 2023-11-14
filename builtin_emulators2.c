#include "shell.h"

/**
 * _myhistory - print the history of used commands
 * @info: struct contain arguments
 * Return: 0
*/
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - remove alias ( Unsets an alias )
 * @info: first parameter struct
 * @str: seconed parameter struct
 * Return: 0 on success or 1 on error
*/
int unset_alias(info_t *info, char *str)
{
	char *sign = _strchr(str, '=');
	int ret;

	if (!sign)
		return (1);
	*sign = '\0';
	ret = delete_node_at_index(&(info->alias),
	get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*sign = '=';
	return (ret);
}

/**
 * set_alias - set alias to string
 * @info: first parameter
 * @str: seconed parameter
 * Return: 0 or 1
*/
int set_alias(info_t *info, char *str)
{
	char *sign = _strchr(str, '=');

	if (!sign)
		return (1);
	if (!*++sign)
	{
		unset_alias(info, str);
		return (0);
	}
	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - print an alas string
 * @node: the alias node
 * Return: 0 or 1
*/
int print_alias(list_t *node)
{
	char *sign = _strchr(node->str, '=');
	char *a = node->str;

	if (node)
	{
		while (a <= sign)
		{
			_putchar(*a);
			a++;
		}
		_putchar('\'');
		_puts(sign + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - manages shell aliases
 * @info: struct contain arguments
 * Return: 0
*/
int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node_alias = NULL;

	if (info->argc == 1)
	{
		node_alias = info->alias;
		while (node_alias)
		{
			print_alias(node_alias);
			node_alias = node_alias->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
		{
			if (set_alias(info, info->argv[i]) != 0)
				return (1);
		}
		else
		{
			node_alias = node_starts_with(info->alias, info->argv[i], '=');
			if (node_alias)
				print_alias(node_alias);
			else
			{
				print_error(info, "alias: ");
				print_error(info, info->argv[i]);
				print_error(info, ": not found\n");
				return (1);
			}
		}
	}
	return (0);
}
