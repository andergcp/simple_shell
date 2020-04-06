#include "shell.h"
/**
 *
 *
 *
 */
char *_getptr()
{
	char *ptr = NULL;
	size_t i;
	int x;

	x = getline(&ptr, &i, stdin);
	if (x > 1)
		return (ptr);
	else
		return (NULL);
}
/**
 *
 *
 *
 */
char **_getoken(char *ptr)
{
	char **args = NULL, *ptraux = NULL;
	int i = 0, sizeP = 1;

	if (!ptr)
		return (NULL);
	while (ptr[i])
	{
		if (ptr[i] == ' ')
			sizeP++;
		i++;
	}
	args = malloc((sizeP + 1) * sizeof(char *)), sizeP = 0;
	if (!args)
		return (NULL);
	ptraux = strtok(ptr, " \n");	
	while(ptraux)
	{
		args[sizeP] = ptraux;
		ptraux = strtok(NULL, " \n");
		sizeP++;
	}
	args[sizeP] = NULL;
	return (args);
}
/**
 *
 *
 *
 */
void _execute(char **args, char **argv)
{
	pid_t f_pid;

	f_pid = fork();
	if (f_pid == -1)
		perror(argv[0]);
	if (f_pid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
			perror(argv[0]);
		exit(0);
	}
	wait(NULL);
}
/**
 * exe_command - execute passed command from main
 * @arg: path name
 */
void exe_command(char *arg)
{
	int ansExe = 0, len = 0;
	pid_t ansFo = 0;
	char *ptr, *argv[2];

	while (arg[len] != '\n')
		len++;
	ptr = malloc(len + 1);
	if (!ptr)
		return;
	ansFo = fork();
	if (ansFo == -1)
		return;
	if (ansFo != 0)
		wait(NULL);
	if (ansFo == 0)
	{
		while (arg[ansExe] != '\n')
			ptr[ansExe] = arg[ansExe], ansExe++;
		ptr[len] = '\0';
		argv[0] = ptr, argv[1] = NULL;
		if (access(argv[0], X_OK) != -1)
			execve(ptr, argv, NULL);
		perror("./shell");
		exit(0);
	}
	free(ptr);
}
