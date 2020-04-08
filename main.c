#include "shell.h"

/**
 * intial - start shell
 */
void initial(char **argv)
{
	char *ptr = NULL;
	char **args = NULL;
	int i;

	do
	{
		signal(SIGINT, SIG_IGN);
		printf("$ ");
		ptr = _getptr(argv);
		if (!ptr)
		{
			free(ptr);
			break;
		}
		args = _getoken(ptr);
		if (!args)
		{
			free(ptr);
			continue;
		}
		i = manage_command(args, argv);
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
	} while(1);
}
/**
 * main - start shell, display prompt
 * Return: always 1
 *
 */
int main(int argc,char **argv, char **env)
{
	int i = isatty(STDOUT_FILENO);
	initial(argv);
	return (1);
}
