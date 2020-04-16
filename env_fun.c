#include "shell.h"
/**
 * _addnode - add node to linked list
 * @m_v: general struct
 * @name: name of node
 * @value: value of node
 */
void _addnode(vari *m_v, char *name, char *value)
{
	env_v *tmp = m_v->p_env, *ptr = NULL;

	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
	}
	ptr = malloc(sizeof(env_v));
	if (!ptr)
		return;
	ptr->name = _strdup(name);
	ptr->value = _strdup(value);
	ptr->next = NULL;
	if (tmp)
		tmp->next = ptr;
	else
		m_v->p_env = ptr;
}
/**
 * _getnode - get node to linked list
 * @m_v: general struct
 * @name: name of node
 * Return: value of node
 */
char *_getnode(vari *m_v, char *name)
{
	env_v *tmp = m_v->p_env;

	while (tmp->next)
	{
		if (_strcmp(tmp->name, name) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
/**
 * _getenv - set values of liked list
 * @m_v: general struct
 */
void _getenv(vari *m_v)
{
	int i, j;

	for (i = 0; m_v->env[i]; i++)
	{
		for (j = 0; m_v->env[i][j] != '='; j++)
			;
		m_v->env[i][j] = '\0', j++;
		_addnode(m_v, m_v->env[i], (m_v->env[i] + j));
		m_v->env[i][j - 1] = '=';

	}
}
/**
 * clear_env - free linked list of environment variables
 * @m_v: general struct
 */
void clear_env(vari *m_v)
{
	env_v *en = m_v->p_env, *tmp;

	while (en)
	{
		tmp = en;
		free(en->name);
		free(en->value);
		en = en->next;
		free(tmp);
	}
}
