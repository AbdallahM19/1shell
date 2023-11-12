#include "shell.h"

void execute_command(char *command, int interactive)
{
	pid_t pid;
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
	{
		return;
	}

	if (_strcmp(args[0], "exit") == 0)
	{
		if (interactive)
			exit(EXIT_SUCCESS);
	}

	if (_strcmp(args[0], "cd") == 0)
	{
		if (args[1] == NULL)
		{
			fprintf(stderr, "cd: missing argument\n");
			return;
		}
		if (chdir(args[1]) != 0)
		{
			perror("chdir");
		}

		return;
	}

	if (_strcmp(args[0], "pwd") == 0)
	{
		char cwd[READ_BUF_SIZE];
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			printf("%s\n", cwd);
		}
		else
		{
			perror("getcwd");
		}
		return;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execvp(args[0], args);
		perror("execvp");
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
    char buffer[BUF_Wr_ON];
    int interactive = isatty(STDIN_FILENO);

    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            perror("Error opening file");
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
