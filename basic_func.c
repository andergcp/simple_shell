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
		array_comm[1].command = "help1";
		array_comm[1].command_function = comm_he;
		array_comm[2].command = "exit";
		array_comm[2].command_function = comm_ex;
		array_comm[3].command = "env";
		array_comm[3].command_function = comm_en;
		array_comm[4].command = "history";
		array_comm[4].command_function = comm_his;
		array_comm[5].command = "unsetenv";
		array_comm[5].command_function = comm_unset;
		array_comm[6].command = "setenv";
		array_comm[6].command_function = comm_set;
		array_comm[7].command = NULL;
		array_comm[7].command_function = NULL;
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
	int i = 0;

	if (!(m_v->ptr[0]) == '\n')
		return;
	m_v->args = _strtok_line(m_v->ptr);
	if (!(m_v->args))
		return ;
}
/**
 * _execute - execute command
 * @args: arrays of tokens
 * @argv: arguments of main
 */
void _execute(variables *m_v, char *args)
{
	pid_t f_pid;
	struct stat aux_stat;
	int status;
	DIR *dir = NULL;

	if (args == NULL)
	{
		dir = opendir(m_v->args[0]);
		if (dir && (_strcmp(m_v->args[0], ".") != 0))
		{
			error_msg(m_v, "Permission denied"), m_v->status = 126;
			closedir(dir);
			return;
		}
		else if (stat(m_v->args[0], &aux_stat) == -1)
		{
			error_msg(m_v, "not found"), m_v->status = 127;
			return;
		}
		else if (access(m_v->args[0], X_OK) == -1)
		{
			error_msg(m_v, "Permission denied"), m_v->status = 126;
			return;
		}
		args = m_v->args[0];
	}
	f_pid = fork();
	if (f_pid == -1)
		error_msg(m_v, "fork failed");
	if (f_pid == 0)
	{
		execve(args, m_v->args, NULL);
		free(m_v->args);
		_exit(2);
	}
	waitpid(f_pid, &status, WUNTRACED);
	m_v->status = WEXITSTATUS(status);
}
/**
 * manage_command - handles the command line search
 * @m_v: general struct
 * Return: 0 in right return, and -1 when failed
 */
int manage_command(variables *m_v)
{
	int i;
	char *hp_arg = NULL;
	struct stat aux_stat;
	
	if (m_v->diccio)
	{
		for (i = 0; m_v->diccio[i].command; i++)
			if (_strcmp(m_v->diccio[i].command, m_v->args[0]) == 0)
			{				
				i = m_v->diccio[i].command_function(m_v);
				return (i);
			}
	}
	else
		return (-1);
	hp_arg = handle_path(m_v);
	_execute(m_v, hp_arg);
	free(hp_arg);
	return (0);
}
