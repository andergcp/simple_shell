#include "shell.h"
/**
 * handle_path - split ttokenize the path look for a command in PATH
 * @m_v: structure of variables used in the program
 * Return: when success pointer to the right path, otherwise NULL
 */
char *handle_path(variables *m_v)
{
	char *aux_path = get_path(m_v);
	char *dup_path = NULL;
	char *buffer = malloc(1024);
	char **paths = NULL;
	int i = 0, size = 1, c_buff = 0;
	DIR *dir = NULL;
	struct stat aux_stat;

	if (!buffer)
		return (NULL);
	dup_path = _strdup(aux_path);
	paths = _strtok_path(dup_path);
	if (!paths)
		return (free(dup_path), NULL);
	size = 0;
/* concatenate path with command and validate it */
	while (paths[size])
	{
		i = 0, c_buff = 0;
		while (paths[size][i])
			buffer[c_buff] = paths[size][i], i++, c_buff++;
		buffer[c_buff] = '/', c_buff++;
		i = 0;
		while (m_v->args[0][i])
			buffer[c_buff] = m_v->args[0][i], i++, c_buff++;
		buffer[c_buff] = '\0';
		dir = opendir(buffer);
		if (dir == NULL)
			if (stat(buffer, &aux_stat) != -1)
				if (access(buffer, X_OK) == 0)
					return (clear_paths(paths), free(paths), free(dup_path), buffer);
		size++;
		c_buf(buffer);
	}
	free(dup_path), size = 0;
	clear_paths(paths);
	free(paths), free(buffer);
	return (NULL);
}

/**
 * _getptr - get new line
 * @m_v: structure of variables used in the program
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
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "\n", 2);
		free(ptr);
		m_v->ptr = NULL;
	}
}
/**
 * _getoken - split line into tokens
 * @m_v: structure of variables used in the program
 * Return; array of tokens
 */
void _getoken(variables *m_v)
{
	if ((m_v->ptr[0]) == '\n')
		return;
	m_v->args = _strtok_line(m_v->ptr);
	if (!(m_v->args))
		return;
}
/**
 * _execute - execute command
 * @args: arrays of tokens
 * @m_v: structure of variables used in the program
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
 * @m_v: structure of variables used in the program
 * Return: 0 in right return, and -1 when failed
 */
int manage_command(variables *m_v)
{
	int i;
	char *hp_arg = NULL;

	if (m_v->diccio)
	{
		for (i = 0; m_v->diccio[i].command; i++)
		{
			if (_strcmp(m_v->diccio[i].command, m_v->args[0]) == 0)
			{
				i = m_v->diccio[i].command_function(m_v);
				return (i);
			}
		}
	}
	else
		return (-1);
	hp_arg = handle_path(m_v);
	_execute(m_v, hp_arg);
	free(hp_arg);
	return (0);
}
