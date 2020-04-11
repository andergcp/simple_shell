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
void _getptr(variables *m_v)
{
	size_t i;
	int x;
	char *ptr = NULL;

	x = getline(&ptr, &i, stdin);
	if (x > 0)
	{
		m_v->ptr = ptr;
		return;
	}
	else
	{
		if (isatty(0))
			write(STDOUT_FILENO, "\n", 1);
		free(ptr);
		m_v->ptr = NULL;
	}
}
/**
 * _getoken - split line into tokens
 * @ptr: pointer of line
 * Return; array of tokens
 */
void _getoken(variables *m_v)
{
	char *ptraux = NULL;
	int i = 0, sizeP = 1;

	if (!(m_v->ptr[0]) == '\n')
		return;
	while (m_v->ptr[i])
	{
		if ((m_v->ptr[i] != ' ' && m_v->ptr[i] != '\t' && m_v->ptr[i] != '\n') &&
		    (i == 0|| m_v->ptr[i - 1] == '\t' || m_v->ptr[i - 1] == ' '))
			sizeP++;
		i++;
	}
	m_v->args = malloc(sizeP * sizeof(char *)), sizeP = 0;
	if (!(m_v->args))
		return ;
	ptraux = strtok(m_v->ptr, " \t\n");
	while(ptraux)
	{
		m_v->args[sizeP] = ptraux;
		ptraux = strtok(NULL, " \t\n");
		sizeP++;
	}
	m_v->args[sizeP] = NULL;
}
/**
 * _execute - execute command
 * @args: arrays of tokens
 * @argv: arguments of main
 */
void _execute(variables *m_v)
{
	pid_t f_pid;
	struct stat aux_stat;

	if (stat(m_v->args[0], &aux_stat) == -1)
		error_msg(m_v, "not found"), m_v->status = 127;
	else if (access(m_v->args[0], X_OK) == -1)
		error_msg(m_v, "Permission denied"), m_v->status = 126;
	else
	{
		f_pid = fork();
		if (f_pid == -1)
			error_msg(m_v, "fork failed");
		if (f_pid == 0)
		{
			if (execve(m_v->args[0], m_v->args, NULL) == -1)
				error_msg(m_v, "execution failed");
			free(m_v->args);
			exit(2);
		}
		wait(NULL);
	}
}

int manage_command(variables *m_v)
{
	inside *diccio = dic_command();
	int i;
	char *hp_arg = NULL;
	struct stat aux_stat;
	
	if (diccio)
	{
		for (i = 0; diccio[i].command; i++)
			if (_strcmp(diccio[i].command, m_v->args[0]) == 0)
			{				
				free(diccio);
				return (diccio[i].command_function(m_v));
			}
	}
	else
		return (free (diccio), -1);
	hp_arg = handle_path(m_v);
	if (hp_arg)
		m_v->args[0] = hp_arg;
	free (diccio);
	_execute(m_v);
	free(hp_arg);
	return (0);
}
