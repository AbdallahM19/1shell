#include "shell.h"

/**
 * _myexit - exit the program (Handles the 'exit' command)
 * @info: structure contain information
 * Return:
 * -2: specified exit status.
 * 1: an illegal number as the exit status.
*/
int _myexit(info_t *info)
{
	int exit_check;

	if (info->argv[1])
	{
		exit_check = _erratoi(info->argv[1]);
		if (exit_check == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory of the process.
 * @info: structure contain information
 * Return: Always 0
*/
int _mycd(info_t *info)
{
	char *curr_dir, *dir, buffer[1024];
	int chdir_ret;

	curr_dir = getcwd(buffer, 1024);
	if (!curr_dir)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		dir = _getenv(info, "OLDPWD=");
		if (!dir)
		{
			_puts(curr_dir);
			_putchar('\n');
			return (1);
		}
		_puts(dir), _putchar('\n');
		chdir_ret = chdir(dir);
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
		return (1);
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - displays information about
 * shell commands or functions
 * @info: structure contain information
 * Return: Always 0
*/
int _myhelp(info_t *info)
{
	char **p;

	p = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*p);
	return (0);
}
