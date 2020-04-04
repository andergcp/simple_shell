#include "shell.h"
/**
 * main - start shell, display prompt
 * Return: always 1
 *
 */
int main(void)
{
	char *line = NULL;
	size_t len;
	int x = 1;

	printf("$ ");
	while (x != -1)
	{
		x = getline(&line, &len, stdin);
		if (x != 1)
			exe_command(line);
		printf("$ ");
	}
	free(line);
	return (1);
}
