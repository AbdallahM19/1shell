#include "shell.h"
/**
 * find_builtin - finds a builtin command
 * 
 * @info: struct include arguments
 * 
 * Return: -1 or 0 or -2 or 1
*
int find_builtin(info_t *info)
{
	int i, built_in_ret = -1;

	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsentenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
		}
	return (built_in_ret);
}*/

/**
 * find_cmd - finds a command in path
 * @info: struct argument
 * Return: void
*/
/*void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];

	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->argv[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;
	path = find_path(info, _getenv(info, "PATH= "), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive_mode || _getenv(info, "PATH=") ||
			info->argv[0][0] == '/' )&&  is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}*/

/**
 * fork_cmd - forks a process
 * @info: struct include arguments
 * Return: void

void fork_cmd(info_t *info)
{
	pid_t child_pid;
	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error: ");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission donied\n");
		}
	}
}*/
