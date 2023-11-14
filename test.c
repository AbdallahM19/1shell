#include "shell.h"

int file_mode(char **av, info_t *info)
{
    	int fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
        return (EXIT_SUCCESS);
}
/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
        file_mode(av, &info);
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}

/*
#include "shell.h"
void execute_cat_command(char *filename)
{
    pid_t pid = fork();
    char *cat_args[3];
    if (pid < 0)
    {
        fprintf(stderr, "Fork failed\n");
        return;
    }
    else if (pid == 0)
    {
        cat_args[0] = "/bin/cat";
        cat_args[1] = filename;
        cat_args[2] = NULL;
            execve(cat_args[0], cat_args, NULL);
        fprintf(stderr, "Execve failed\n");
        exit(1);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
    }
}
void execute_command(char *command, int interactive)
{
	pid_t pid;
	char *path, *pas;
	char *args[READ_BUF_SIZE];
	int i = 0;
  	char *token = strtok_custom(command, " \n");
	while (token != NULL && i < READ_BUF_SIZE- 1)
	{
		args[i++] = token;
		token = strtok_custom(NULL, " \n");
	}
	args[i] = NULL;
	if (args[0] == NULL)
		return;
	if (_strcmp(args[0], "exit") == 0)
		if (interactive)
			exit(EXIT_SUCCESS);
	if (_strcmp(args[0], "cd") == 0)
	{
		if (args[1] == NULL)
		{
			fprintf(stderr, "cd: missing argument\n");
			return;
		}
		if (chdir(args[1]) != 0)
			perror("chdir");
		return;
	}
	if (_strcmp(args[0], "pwd") == 0)
	{
		char cwd[READ_BUF_SIZE];
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			printf("%s\n", cwd);
		else
			perror("getcwd");
		return;
	}
	    else if (_strcmp(args[0], "cat") == 0)
    {
         execute_cat_command(args[0]);
		        return;
    }
	if (args[0][0] == '/')
	{
		if (access(args[0], X_OK) == 0)
		{
			pid = fork();
			if (pid < 0)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
			else if (pid == 0)
			{
				execve(args[0], args, NULL);
				perror("execve"); 
				exit(EXIT_FAILURE);
			}
			else
			{
				int status;
				if (interactive)
					waitpid(pid, &status, 0);
			}
			return;
		}
		else
		{
			fprintf(stderr, "%s: command not found\n", args[0]);
			return;
		}
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		path = getenv("PATH");
		pas = strtok_custom(path, ":");
		while (pas != NULL) {
			char potential_command[READ_BUF_SIZE];
			sprintf(potential_command, "%s/%s", pas, args[0]);
			if (access(potential_command, X_OK) == 0) {
				execve(potential_command, args, NULL);
				perror("execve"); 
				exit(EXIT_FAILURE);
			}
			pas = strtok_custom(NULL, ":");
		}
		exit(EXIT_FAILURE);
	}
	else
	{
		int status;
		if (interactive)
			waitpid(pid, &status, 0);
	}
}

void non_interactive()
{
	char buffer[BUF_Wr_ON];

	while (1) {
		fflush(stdout);

		if (fgets(buffer, BUF_Wr_ON, stdin) == NULL) {
			break;
		}

		buffer[strcspn(buffer, "\n")] = '\0';

		if (_strcmp(buffer, "exit") == 0)
			break;
		execute_command(buffer, 1);
	}
}
void interactive_mode()
{
	char buffer[BUF_Wr_ON];
   
	while (1) {
		printf("($) ");
		fflush(stdout);

		if (fgets(buffer, BUF_Wr_ON, stdin) == NULL) {
			printf("\n");
			break;
		}

		buffer[strcspn(buffer, "\n")] = '\0';

		if (_strcmp(buffer, "exit") == 0)
			break;
		execute_command(buffer, 1);
	}
}

int main(int argc, char *argv[]) {
 int interactive = isatty(STDIN_FILENO);
    char buffer[BUF_Wr_ON];
info_t *info = malloc(sizeof(info_t));
if (info == NULL)
{
    fprintf(stderr, "Cannot allocate memory\n");
    exit(EXIT_FAILURE);
}
info->fname = argv[1];
info->line_count = 1;
info->argv = argv;

    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            print_error(info, "not found");
            exit(EXIT_FAILURE);
        }
        while (fgets(buffer, BUF_Wr_ON, file) != NULL) {
            buffer[strcspn(buffer, "\n")] = '\0';
            execute_command(buffer, interactive);
        }
        fclose(file);
    } else {
        if (interactive) {
            interactive_mode();
        } else {
            non_interactive();
        }
    }
    return 0;
}
*/
