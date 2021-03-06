#include "shell.h"
/**
 * dic_command - create a new diccionary
 * Return: pointer that point to new diccionary
 */
inside *dic_command()
{
	inside *array_comm = malloc(sizeof(inside) * 7);

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
		array_comm[4].command = "unsetenv";
		array_comm[4].command_function = comm_unset;
		array_comm[4].help = "./help_files/unsetenv.txt";
		array_comm[5].command = "setenv";
		array_comm[5].command_function = comm_set;
		array_comm[5].help = "./help_files/setenv.txt";
		array_comm[6].command = NULL;
		array_comm[6].command_function = NULL;
		array_comm[6].help = NULL;

		return (array_comm);
	}
	return (NULL);
}
/**
 * error_msg - print error message
 * @m_v: General struct
 * @msg: message to print
 * @option: Set option of error printed
 */
void error_msg(variables *m_v, char *msg, int option)
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
	if (option == 2)
	{
		len = _strlen(m_v->args[1]);
		_strcpy((buffer + sum), m_v->args[1]);
		sum += len;
	}
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
		if (ptr[i] == '#' && (i == 0 || ptr[i + 1] == ' ' || ptr[i - 1] == ' '))
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
		paths[i] = _strdup(token);
		token = strtok(NULL, ":");
	}
	paths[i] = NULL;
	free(token);
	return (paths);
}
/**
 * valid_path - validates if the path is ok
 * @aux_path: pointer to PATH values
 * Return: 1 when success, 0 when fails
 */
int valid_path(char *aux_path)
{
	int i = 0;

	while (aux_path[i])
	{
		if (aux_path[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}
