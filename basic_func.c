#include "shell.h"
/**
 * dic_command - create a new diccionary
 * Return: pointer that point to new diccionary
 */
inside *dic_command()
{
	inside *array_comm = malloc(sizeof(inside) * 6);
	
	if (array_comm)
	{
		array_comm[0].command = "cd";
		array_comm[0].command_function = comm_cd; 
		array_comm[1].command = "help";
		array_comm[1].command_function = comm_he;
		array_comm[2].command = "exit";
		array_comm[2].command_function = comm_ex;
		array_comm[3].command = "env";
		array_comm[3].command_function = comm_en;
		array_comm[4].command = "history";
		array_comm[4].command_function = comm_his;
		array_comm[5].command = NULL;
		array_comm[5].command_function = NULL;
		return (array_comm);
	}
	return (NULL);
}
/**
 * _getptr - get new line
 * Return: pointer that point to new line
 */
char *_getptr(char **argv)
{
	char *ptr = NULL;
	size_t i;
	int x;

	x = getline(&ptr, &i, stdin);
	printf("%d\n", x);
	if (x > 0)
		return (ptr);
	else
	{
		if (isatty(0))
			write(STDOUT_FILENO, "\n", 1);
		return (free(ptr), NULL);
	}
}
/**
 * _getoken - split line into tokens
 * @ptr: pointer of line
 * Return; array of tokens
 */
char **_getoken(char *ptr)
{
	char **args = NULL, *ptraux = NULL;
	int i = 0, sizeP = 1;

	if (!ptr || ptr[0] == '\n')
		return (NULL);
	while (ptr[i])
	{
		if ((ptr[i] != ' ' && ptr[i] != '\t' && ptr[i] != '\n') &&
		    (i == 0|| ptr[i - 1] == '\t' || ptr[i - 1] == ' '))
			sizeP++;
		i++;
	}
	args = malloc(sizeP * sizeof(char *)), sizeP = 0;
	if (!args)
		return (NULL);
	ptraux = strtok(ptr, " \t\n");
	while(ptraux)
	{
		args[sizeP] = ptraux;
		ptraux = strtok(NULL, " \t\n");
		sizeP++;
	}
	args[sizeP] = NULL;
	return (args);
}
/**
 * _execute - execute command
 * @args: arrays of tokens
 * @argv: arguments of main
 */
void _execute(char **args, char **argv)
{
	pid_t f_pid;
	struct stat aux_stat;

	if (stat(args[0], &aux_stat) == -1)
		perror(argv[0]);
	else if (access(args[0], X_OK) == -1)
		perror(argv[0]);
	else
	{
		f_pid = fork();
		if (f_pid == -1)
			perror(argv[0]);
		if (f_pid == 0)
		{
			if (execve(args[0], args, NULL) == -1)
				perror(argv[0]);
			free(args);
			exit(2);
		}
		wait(NULL);
	}
}

int manage_command(char **args, char **argv, char **env)
{
	inside *diccio = dic_command();
	int i;
	char *hp_arg = NULL;
	struct stat aux_stat;
	
	if (stat(args[0], &aux_stat) == -1)
	{
		if (diccio)
		{
			if (args[0])
			{
				for (i = 0; diccio[i].command; i++)
					if (_strcmp(diccio[i].command, args[0]) == 0)
						return (free (diccio), diccio[i].command_function(args));
			}
			else
				return (free (diccio), -2);
		}
		else
			return (free (diccio), -1);
		hp_arg = handle_path(args, env);
		if (hp_arg)
			args[0] = hp_arg;
	}
	free (diccio);
	_execute(args, argv);
	free(hp_arg);
	return (0);
}
