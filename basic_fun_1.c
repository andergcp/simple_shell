#include "shell.h"
/**
 * handle_path - split ttokenize the path look for a command in PATH
 * @m_v: structure of variables used in the program
 * Return: when success pointer to the right path, otherwise NULL
 */
char *handle_path(variables *m_v)
{
	char *aux_path = get_path(m_v), **paths = NULL;
	char *dup_path = NULL, *buffer = NULL;
	int i = 0, size = 0, c_buff = 0;
	DIR *dir = NULL;
	struct stat aux_stat;

	if (_strcmp(m_v->args[0], ".") == 0)
		return (NULL);
	dir = opendir(m_v->args[0]);
	if (dir)
		return (error_msg(m_v, "Permission denied"), m_v->status = 126,
			closedir(dir), NULL);
	closedir(dir);
	buffer = malloc(1024);
	if (!buffer)
		return (NULL);
	dup_path = _strdup(aux_path);
	paths = _strtok_path(dup_path);
	if (!paths)
		return (free(dup_path), NULL);
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
		if (stat(buffer, &aux_stat) != -1)
			if (!access(buffer, X_OK))
				return (clear_paths(paths), free(paths), free(dup_path),
					_execute(m_v, buffer), buffer);
		size++, c_buf(buffer);
	}
	free(dup_path), clear_paths(paths);
	free(paths), free(buffer);
	_execute(m_v, NULL);
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
	char **env = NULL;

	if (args == NULL)
	{
		if (stat(m_v->args[0], &aux_stat) == -1)
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
	{
		m_v->status = -1;
		error_msg(m_v, "Error spawning child process\n");
	}
	env = _envtoarray(m_v);
	if (f_pid == 0)
	{
		execve(args, m_v->args, env);
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
	free(hp_arg);
	return (0);
}
