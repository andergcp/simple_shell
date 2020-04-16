#include "shell.h"
/**
 * manage_command - handles the command line search
 * @m_v: structure of variables used in the program
 * Return: 0 in right return, and -1 when failed
 */
int manage_command(vari *m_v)
{
	DIR *dir = NULL;

	dir = opendir(m_v->args[0]);
	if (dir)
		return (error_msg(m_v, "Permission denied"), m_v->status = 126,
			closedir(dir), 0);
	closedir(dir);
	_execute(m_v);
	return (0);
}

/**
 * _execute - execute command
 * @m_v: structure of variables used in the program
 */
void _execute(vari *m_v)
{
	pid_t f_pid;
	struct stat aux_stat;
	int status;

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
	f_pid = fork();
	if (f_pid == -1)
	{
		m_v->status = -1;
		error_msg(m_v, "Error spawning child process\n");
	}
	if (f_pid == 0)
	{
		execve(m_v->args[0], m_v->args, m_v->env);
		free(m_v->args);
		_exit(2);
	}
	waitpid(f_pid, &status, WUNTRACED);
	m_v->status = WEXITSTATUS(status);
}
