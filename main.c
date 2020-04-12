#include "shell.h"
/**
 * initialize - initialices variables to use
 *
 *
 */
variables *initialize(char **argv, char **env)
{
	variables *m_v = malloc(sizeof(variables));

	if (!m_v)
		return (NULL);
	m_v->argv = argv;
	m_v->env = env;
	m_v->ptr = NULL;
	m_v->args = NULL;
	m_v->status = 0;
	m_v->prompt_n = 0;

	return (m_v);
}
/**
 * handle - handle signa interruption
 */
void handle(int m)
{
	write(STDOUT_FILENO, "\n$ ", 3);
}
/**
 * initial - start shell
 * @argv: Name of executable
 * @env: variables of environment
 */
void initial(char **argv, char **env)
{
	variables *m_v = initialize(argv, env);
	int i;

	if(!m_v)
		return;
	signal(SIGINT, handle);
	//signal(SIGTSTP, SIG_IGN);
	do {
		m_v->prompt_n += 1;
		if (isatty(0))
			printf("$ ");
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
			write(STDOUT_FILENO, "No alloc diccio\n", 24);
		free(m_v->args);
		free(m_v->ptr);
	} while (1);
	i = m_v->status;
	free(m_v);
<<<<<<< HEAD
	exit(i);
=======
	exit(m_v->status);
>>>>>>> a9e52f3455dda8c1e7cea49ec19a3ae25624d289
}
/**
 * main - start shell, display prompt
 * Return: always 1
 * @argc: counter of arguments
 * @argv: arguments
 * @env: environment varibles
 */
int main(int argc, char **argv, char **env)
{
	initial(argv, env);
	return (1);
}
