#include "shell.h"
/**
 * handle - handle signa interruption
 */
void handle(int m)
{
	write(STDOUT_FILENO, "\n$ ", 3);
}
/**
 * initial - start shell
 * @argv: Name of executable
 * @env: variables of environment
 */
void initial(char **argv, char **env)
{
	char *ptr = NULL;
	char **args = NULL;
	int i;

	signal(SIGINT, handle);
	signal(SIGTSTP, SIG_IGN);
	do {
		if (isatty(0))
			printf("$ ");
		ptr = _getptr(argv);
		if (!ptr)
		{
			free(ptr);
			exit(27);
			break;
		}
		args = _getoken(ptr);
		if (!args)
		{
			free(ptr);
			continue;
		}
		i = manage_command(args, argv, env);
		if (i == -1)
			write(STDOUT_FILENO, "No alloc diccio\n", 24);
		else if (i == -2)
		{
			free(args);
			free(ptr);
			continue;
		}
		free(args);
		free(ptr);
	} while (1);
}
/**
 * main - start shell, display prompt
 * Return: always 1
 * @argc: counter of arguments
 * @argv: arguments
 * @env: environment varibles
 */
int main(int argc, char **argv, char **env)
{
	initial(argv, env);
	return (1);
}
