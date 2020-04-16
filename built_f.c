#include "shell.h"
/**
 * dic_command - create a new diccionary
 * Return: pointer that point to new diccionary
 */
inside *dic_command()
{
	inside *array_comm = malloc(sizeof(inside) * 3);

	if (array_comm)
	{
		array_comm[0].command = "exit";
		array_comm[0].command_function = comm_ex;
		array_comm[0].help = "./help_files/exit.txt";
		array_comm[1].command = "env";
		array_comm[1].command_function = comm_en;
		array_comm[1].help = "./help_files/env.txt";
		array_comm[2].command = NULL;
		array_comm[2].command_function = NULL;
		array_comm[2].help = NULL;

		return (array_comm);
	}
	return (NULL);
}

/**
 * comm_ex - exits the program
 * @m_v: structure of variables used in the program
 * Return: When argumente is stablished return this integer,
 * if don't return the last status, when fails return -2
 */
void comm_ex(vari *m_v)
{
	int i;

	if (m_v->args[1] == NULL && m_v->args[0] != NULL)
	{
		free(m_v->args);
		free(m_v->ptr);
		free(m_v->diccio);
		clear_env(m_v);
		i = m_v->status;
		free(m_v);
		exit(i);
	}
	else if (m_v->args[1] != NULL && m_v->args[0] != NULL)
	{
		i = _atoi(m_v->args[1]);
		if (i <= -1)
		{
			error_msg(m_v, "Illegal number");
			m_v->status = 2;
		}
		free(m_v->args);
		free(m_v->ptr);
		free(m_v->diccio);
		clear_env(m_v);
		free(m_v);
		exit(i);
	}
}

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

