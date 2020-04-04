#include "shell.h"
/**
 * exe_command - execute passed command from main
 * @arg: path name
 */
void exe_command(char *arg)
{
	int ansExe = 0, len = 0, x = 0;
	pid_t ansFo = 0;
	char *ptr, *argv[2];

	while (arg[len] != '\n')
		len++;
	ptr = malloc(len + 1);
	if (!ptr)
		return;
	else
	{
		ansFo = fork();
		if (ansFo == -1)
			return;
		if (ansFo != 0)
			sleep(1);
		if (ansFo == 0)
		{	
			while (arg[ansExe] != '\n')
				ptr[ansExe] = arg[ansExe], ansExe++;
			ptr[len] = '\0';
			argv[0] = ptr, argv[1] = NULL;
			x = execve(ptr, argv, NULL);
			printf("Error\n");
			exit(0);
		}	
	}
	free(ptr);
}
