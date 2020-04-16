#include "shell.h"
/**
 * set_env_v - set value of environment struct
 * @env: general Double pointer to enviroment variables
 * Return: pointer that point to first node
 */
env_v *set_env_v(char **env)
{
	int i, j, index = 0;
	char *ptr = NULL;
	env_v *en = malloc(sizeof(env_v));
	env_v *head = en, *prev = NULL;

	en->next = NULL;
	for (i = 0; env[i]; i++)
	{
		if (i != 0)
		{
			prev = en;
			en = malloc(sizeof(env_v));
			prev->next = en;
		}
/*get name of variable*/
		for (j = 0; env[i][j] != '='; j++)
			;
		env[i][j] = '\0', j++;
/*set name of variable*/
		ptr = malloc(j);
		if (!ptr)
			return (NULL);
		_strcpy(ptr, env[i]);
		en->name = ptr;
/*get value of variable*/
		for (index = 0; env[i][j + index]; index++)
			;
		ptr = malloc(index + 1);
		if (!ptr)
			return (NULL);
		_strcpy(ptr, (env[i] + j));
		ptr[index] = '\0';
		en->value = ptr;
		en->next = NULL;
	}
	return (head);
}
/**
 * clear_env - free linked list of environment variables
 * @m_v: general struct
 */
void clear_env(variables *m_v)
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

/**
 * get_env - get environment variable value
 * @m_v: structure of variables used in the program
 * @name: Name of required variable
 * Return: pointer to value
 */
char *get_env(variables *m_v, char *name)
{
	env_v *en = m_v->p_env;

	while (en)
	{
		if (_strcmp(en->name, name) == 0)
			return (en->value);
		en = en->next;
	}
	return (NULL);
}
/**
 * set_env - Set a value of a variable in enviroment
 * @m_v: structure of variables used in the program
 * @name: name of the variable to asign
 * @value: Value to asign to the variable
 */
void set_env(variables *m_v, char *name, char *value)
{
	char *ptr = NULL;
	env_v *tmp = NULL, *en = m_v->p_env;
	int len;

	while (en)
	{
		if (_strcmp(en->name, name) == 0)
		{
			len = _strlen(value);
			ptr = malloc(len + 1);
			_strcpy(ptr, value);
			ptr[len] = '\0';
			free(en->value);
			en->value = ptr;
			return;
		}
		if (en->next == NULL)
			break;
		en = en->next;
	}
	tmp = malloc(sizeof(env_v));
	tmp->next = NULL;
	len = _strlen(name);
	ptr = malloc(len + 1);
	_strcpy(ptr, name);
	ptr[len] = '\0';
	tmp->name = ptr;
	len = _strlen(value);
	ptr = malloc(len + 1);
	_strcpy(ptr, value);
	ptr[len] = '\0';
	tmp->value = ptr;
	en->next = tmp;
}
