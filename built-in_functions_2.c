#include "shell.h"
/**
 * unsetenv - remove an environment variable
 * @m_v: general struct
 */
int comm_unset(variables *m_v)
{
	env_v *tmp, *en = m_v->p_env;
	
	if (_strcmp(en->name, m_v->args[1]) == 0)
	{
		m_v->p_env = m_v->p_env->next;
		free(en->name);
		free(en->value);
		free(en);
		m_v->status = 0;
		return (0);
	}
	while (en)
	{
		tmp = en;
		en = en->next;
		if (_strcmp(en->name, m_v->args[1]) == 0)
		{
			tmp->next = tmp->next->next;
			free(en->name);
			free(en->value);
			free(en);
			m_v->status = 0;
			return (0);
		}
	}
	m_v->status = 0;
	return (0);
}

int comm_set(variables *m_v)
{
	char *ptr = NULL;
	env_v *tmp = NULL, *en = m_v->p_env;
	int len;

	if (!(m_v->args[2]) || !(m_v->args[1]))
		return (printf("Hola mundo\n"), 0);
	set_env(m_v, m_v->args[1], m_v->args[2]);
	return (0);
}
