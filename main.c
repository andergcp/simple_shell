#include "shell.h"
/**
 * intial - start shell
 */
void initial(char **argv)
{
	char *ptr = NULL;
	char **args = NULL;

	do
	{
		printf("$ ");
		ptr = _getptr();
		if (!ptr)
			continue;
		args = _getoken(ptr);
		_execute(args, argv);
		free(ptr);
		free(args);
	} while(1);
}
/**
 * main - start shell, display prompt
 * Return: always 1
 *
 */
int main(int argc,char **argv, char **env)
{
	initial(argv);
	return (1);
}
