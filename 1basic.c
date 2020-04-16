#include "shell.h"
/**
 * manage_command - handles the command line search
 * @m_v: structure of variables used in the program
 * Return: 0 in right return, and -1 when failed
 */
int manage_command(vari *m_v)
{
	char **path = NULL, *dup = NULL;
	DIR *dir = NULL;
	char buffer[4096];
	int i;
	struct stat aux_stat;

	dir = opendir(m_v->args[0]);
	if (dir)
		return (error_msg(m_v, "Permission denied"), m_v->status = 126,
			closedir(dir), 0);
	closedir(dir);
	dup = _strdup(_getnode(m_v, "PATH"));
	if (!dup)
		return (0);
	path = _strtok_path(dup);
	if (path || path[0] != '\0')
	{
		for (i = 0; path[i]; i++)
		{
			c_buf(buffer);
			_strcat(buffer, path[i]);
			_strcat(buffer, "/");
			_strcat(buffer, m_v->args[0]);
			if (stat(buffer, &aux_stat) != -1)
				if (!access(buffer, X_OK))
					return (clear_paths(path), free(path), free(dup),
						_execute(m_v, buffer), 0);
			c_buf(buffer);
		}
	}
	clear_paths(path);
	free(path), free(dup);
	_execute(m_v, NULL);
	return (0);
}

/**
 * _execute - execute command
 * @m_v: structure of variables used in the program
 * @path: path of command
 */
void _execute(vari *m_v, char *path)
{
	pid_t f_pid;
	struct stat aux_stat;
	int status;

	if (!path)
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
		path = m_v->args[0];
	}
	f_pid = fork();
	if (f_pid == -1)
	{
		m_v->status = -1;
		error_msg(m_v, "Error spawning child process\n");
	}
	if (f_pid == 0)
	{
		execve(path, m_v->args, m_v->env);
		free(m_v->args);
		_exit(2);
	}
	waitpid(f_pid, &status, WUNTRACED);
	m_v->status = WEXITSTATUS(status);
}
