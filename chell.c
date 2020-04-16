#include "shell.h"
/**
 * initialize - initialices variables to use
 * @argv: Arguments received from main
 * Return: Initial values for struct variables
 */
vari *initialize(char **argv)
{
	vari *m_v = malloc(sizeof(vari));

	if (!m_v)
		return (NULL);
	m_v->argv = argv;
	m_v->env = environ;
	m_v->ptr = NULL;
	m_v->args = NULL;
	m_v->status = 0;
	m_v->prompt_n = 0;
	m_v->p_env = NULL;
	m_v->diccio = dic_command();

	return (m_v);
}
/**
 * initial - start shell
 * @argv: Name of executable
 */
void initial(char **argv)
{
	vari *m_v = initialize(argv);
	int ans, i = 0;
	size_t x;

	if (!m_v)
		return;
	_getenv(m_v);
	do {
		m_v->prompt_n += 1;
		m_v->ptr = NULL;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);
		ans = getline(&m_v->ptr, &x, stdin);
		if (ans == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}
		_strtok_line(m_v);
		if (!(m_v->args[0]) || _strcmp(m_v->args[0], ".") == 0)
		{
			free(m_v->ptr);
			free(m_v->args);
			continue;
		}
		ans = manage_command(m_v);
		free(m_v->ptr);
		free(m_v->args);
	} while (1);
	i = m_v->status;
	free(m_v->ptr);
	clear_env(m_v);
	free(m_v->diccio), free(m_v);
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
