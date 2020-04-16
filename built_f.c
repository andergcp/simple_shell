#include "shell.h"
/**
 * comm_en - Prints environment variables
 * @m_v: strcture of variables used in the program
 * Return: 0
 */
void comm_en(vari *m_v)
{
	env_v *tmp = m_v->p_env;

	while (tmp)
	{
		write(STDOUT_FILENO, tmp->name, _strlen(tmp->name));
		write(STDOUT_FILENO, "=", 1);
		write(STDOUT_FILENO, tmp->value, _strlen(tmp->value));
		write(STDOUT_FILENO, "\n", 1);
		tmp = tmp->next;
	}
}

