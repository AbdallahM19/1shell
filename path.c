#include "shell.h"

/**
 * is_cmd - check if the command is executable
 * @info: struct include the arguments
 * @path: path of the file
 * Return: 1 or 0
*/
int is_cmd(info_t *info, char *path)
{
	struct stat st;
	(void)info;

	if (!path || stat(path, &st) != 0)
		return (0);
	if (S_ISREG(st.st_mode))
		return (1);
	return (0);
}

/**
 *dup_chars - duplicate char
 *@pathstr: path string
 *@start: index to start
 *@stop: index to stop
 * Return: pointer
*
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}*/
char *dup_chars(char *pathstr, int start, int stop)
{
    static char buf[1024];
    int i = 0, k = 0;

    if (!pathstr)
        return (NULL);
    if (start < 0 || stop > _strlength(pathstr))
        return (NULL);

    for (k = 0, i = start; i < stop; i++)
        if (pathstr[i] != ':')
            buf[k++] = pathstr[i];
    buf[k] = 0;
    return (buf);
}

/**
 * findpath - find the cmd in the path
 * @info: struct include the arguments
 * @pathstr: the PATH
 * @cmd: what we will search
 * Return: the path
*/
char *find_path(info_t *info, char *pathstr, char *cmd)
{
    int i = 0, curr_pos = 0;
    char *path;

    if (!pathstr)
        return (NULL);
    if ((_strlength(cmd) > 2) && starts_with(cmd, "./"))
    {
        if (is_cmd(info, cmd))
            return (cmd);
    }
    while (1)
    {
        if (!pathstr[i] || pathstr[i] == ':')
        {
            path = dup_chars(pathstr, curr_pos, i);
            if (!*path)
                _strcat(path, cmd);
            else
            {
                _strcat(path, "/");
                _strcat(path, cmd);
            }
            if (is_cmd(info, path))
                return (path);
            if (!pathstr[i])
                break;
            curr_pos = i + 1;  
        }
        i++;
    }
    return (NULL);
}