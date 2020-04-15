#include "shell.h"
/**
 * dic_command - create a new diccionary
 * Return: pointer that point to new diccionary
 */
inside *dic_command()
{
	inside *array_comm = malloc(sizeof(inside) * 8);

	if (array_comm)
	{
		array_comm[0].command = "cd";
		array_comm[0].command_function = comm_cd;
		array_comm[0].help = "./help_files/cd.txt";
		array_comm[1].command = "help";
		array_comm[1].command_function = comm_he;
		array_comm[1].help = "./help_files/help.txt";
		array_comm[2].command = "exit";
		array_comm[2].command_function = comm_ex;
		array_comm[2].help = "./help_files/exit.txt";
		array_comm[3].command = "env";
		array_comm[3].command_function = comm_en;
		array_comm[3].help = "./help_files/env.txt";
		array_comm[5].command = "unsetenv";
		array_comm[5].command_function = comm_unset;
		array_comm[5].help = "./help_files/unsetenv.txt";
		array_comm[6].command = "setenv";
		array_comm[6].command_function = comm_set;
		array_comm[6].help = "./help_files/setenv.txt";
		array_comm[7].command = NULL;
		array_comm[7].command_function = NULL;
		array_comm[7].help = NULL;

		return (array_comm);
	}
	return (NULL);
}
/**
 * error_msg - print error message
 * @m_v: General struct
 * @msg: message to print
 */
void error_msg(variables *m_v, char *msg)
{
	char *buffer = malloc(512), *ptr = NULL;
	int len = 0, sum = 0, a = m_v->prompt_n;

	len = _strlen(m_v->argv[0]);
	sum += len, len = 1;
	_strcpy(buffer, m_v->argv[0]);
	_strcpy((buffer + sum), ": ");
	sum += 2;
	while (a / 10 != 0)
		a /= 10, len++;
	ptr = _itoa(m_v->prompt_n);
	_strcpy((buffer + sum), ptr);
	sum += len;
	_strcpy((buffer + sum), ": ");
	sum += 2;
	len = _strlen(m_v->args[0]);
	_strcpy((buffer + sum), m_v->args[0]);
	sum += len;
	_strcpy((buffer + sum), ": ");
	sum += 2;
	len = _strlen(msg);
	_strcpy((buffer + sum), msg);
	sum += len;
	buffer[sum] = '\n', sum++;
	write(STDERR_FILENO, buffer, sum);
	free(buffer);
	free(ptr);
}
/**
 * _strtok_line - split a string
 * @ptr: string to split
 * Return: double pointer to ptr tokenized
 */
char **_strtok_line(char *ptr)
{
	char **args = NULL, *tmp;
	int i = 0, j = 0, sizeP = 0;

	if (!ptr)
		return (NULL);
	while (ptr[i])
	{
		if (ptr[i] == '#')
		{
			tmp = (ptr + i);
			c_buf(tmp);
		}
		else if ((ptr[i] != ' ' && ptr[i] != '\t'
			  && ptr[i] != '\n' && ptr[i] != ';') &&
			 (i == 0 || ptr[i - 1] == '\t' || ptr[i - 1] == ' '))
			sizeP++;
		i++;
	}
	args = malloc(sizeof(char *) * (sizeP + 1)), i = 0;
	if (!args)
		return (NULL);
	tmp = strtok(ptr, " \t\n");
	while (tmp)
	{
		args[j] = tmp;
		tmp = strtok(NULL, " \t\n");
		j++;
	}
	args[j] = NULL;
	if (!args[0])
		return (free(args), NULL);
	return (args);
}
/**
 * get_path - get path line
 * @m_v: structure of variables used in the program
 * Return: pointer that point to path line
 */
char *get_path(variables *m_v)
{
	env_v *en = m_v->p_env;

	while (en)
	{
		if (_strcmp(en->name, "PATH") == 0)
			return (en->value);
		en = en->next;
	}
	return (NULL);
}
/**
 * _strtok_path - tokenize the PATH
 * @ptr: pointer to variable PATH
 * Return: pointer to array of strings with values of PATH
 */
char **_strtok_path(char *ptr)
{
	char **paths = NULL, *token;
	int i = 0, sizeP = 1;

	while (ptr[i])
	{
		if (ptr[i] == ':')
			sizeP++;
		i++;
	}
	paths = malloc(sizeof(char *) * (sizeP + 1));
	if (!paths)
		return (NULL);
	token = strtok(ptr, ":");
	for (i = 0; token; i++)
	{
		paths[i] = strdup(token);
		token = strtok(NULL, ":");
	}
	paths[i] = NULL;
	free(token);
	return (paths);
}
