#include "shell.h"
/**
 * initialize - initialices variables to use
 * @argv: Arguments received from main
 * Return: Initial values for struct variables
 */
variables *initialize(char **argv)
{
	variables *m_v = malloc(sizeof(variables));

	if (!m_v)
		return (NULL);
	m_v->argv = argv;
	m_v->env = environ;
	m_v->ptr = NULL;
	m_v->args = NULL;
	m_v->status = 0;
	m_v->prompt_n = 0;
	m_v->p_env = set_env_v(environ);
	m_v->diccio = dic_command();

	return (m_v);
}
/**
 * handle - handle signa interruption
 * @m: Status Signal received
 */
void handle(__attribute__((unused)) int m)
{
	write(STDOUT_FILENO, "\n$ ", 3);
}
/**
 * initial - start shell
 * @argv: Name of executable
 */
void initial(char **argv)
{
	variables *m_v = initialize(argv);
	int i;

	if (!m_v)
		return;
	signal(SIGINT, handle);
	signal(SIGTSTP, SIG_IGN);
	do {
		m_v->prompt_n += 1;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);
		_getptr(m_v);
		if (!(m_v->ptr))
		{
			free(m_v->ptr);
			break;
		}
		if (m_v->ptr[0] == '\n')
		{
			free(m_v->ptr);
			continue;
		}
		_getoken(m_v);
		if (!(m_v->args))
		{
			free(m_v->ptr);
			continue;
		}
		i = manage_command(m_v);
		if (i == -1)
			write(STDOUT_FILENO, "No alloc diccio\n", 16);
		free(m_v->args);
		free(m_v->ptr);
	} while (1);
	i = m_v->status;
	clear_env(m_v);
	free(m_v->diccio);
	free(m_v);
	exit(i);
}
/**
 * main - start shell, display prompt
 * Return: always 1
 * @argc: counter of arguments
 * @argv: arguments
 */
int main(__attribute__((unused)) int argc, char **argv)
{
	initial(argv);
	return (0);
}
