#include "shell.h"
/**
 * _strtok_path - 
 *
 *
 */
char **_strtok_path(char *ptr)
{
	char **paths = NULL, *ptr1 = malloc(512);
	int len, i = 0, j = 0, sizeP = 1;
	
	while (ptr[i])
	{
		if (ptr[i] == ':')
			sizeP++;
		i++;
	}
	paths = malloc(sizeof(char *) * (sizeP + 1)), i = 0;
	if (!paths)
		return (NULL);
	while (ptr[i])
	{
		if ((ptr[i] == ':') && (i == 0 || ptr[i - 1] == '\0' ||
					ptr[i + 1] == '\0'))
		{
			ptr[i] = '\0';
			getcwd(ptr1, sizeof(char) * 1024);
			paths[j] = ptr1;
			j++;
		}
		else if ((ptr[i] != ':') && (i == 0 || ptr[i - 1] == '\0'))
		{
			paths[j] = (ptr + i);
			j++;
		}
		else if (ptr[i] == ':')
			ptr[i] = '\0';
		i++;
	}
	paths[j] = NULL;
	free(ptr1);
	return (paths);
}
/**
 * set_env_v - set value of environment struct
 * @m_v: general struct
 * Return: pointer that point to first node
 */
env_v *set_env_v(char **env)
{
	int i, j, index = 0;
	char *ptr = NULL;
	env_v *en = malloc(sizeof(env_v));
	env_v *head = en, *prev = NULL;

	en->next = NULL;
	for(i = 0; env[i]; i++)
	{
		if (i != 0)
		{
			prev = en;
			en = malloc(sizeof(env_v));
			prev->next = en;
		}
                //get name of variable
	        for(j = 0; env[i][j] != '='; j++)
			;
		env[i][j] = '\0', j++;
                //set name of variable
		ptr = malloc(j);
		if (!ptr)
			return (NULL);
		_strcpy(ptr, env[i]);
		en->name = ptr;
		//get value of variable
		for (index = 0; env[i][j + index]; index++)
			;
		ptr = malloc(index + 1);
		if(!ptr)
			return (NULL);
		_strcpy(ptr, (env[i] + j));
		ptr[index] = '\0';
		en->value = ptr;
		en->next = NULL;
	}
	return (head);
}

void print_env(variables *m_v)
{
	char *buffer = malloc(1024);
	env_v *en = m_v->p_env; 
	int sum = 0, len, sign_pos;

	if (!buffer)
		return;
	while (en)
	{
		len = _strlen(en->name);
		sign_pos = len;
		len = _strlen(en->value);
		if (len + sum + 1 < 1024)
		{
			_strcpy((buffer + sum), en->name);
			buffer[sign_pos + sum] = '=';
			sum += sign_pos + 1;
			_strcpy((buffer + sum), en->value);
			sum += len;
			buffer[sum] = '\n';
			buffer[sum + 1] = '\0';
			en = en->next, sum++;
		}
		else
		{
			write(STDOUT_FILENO, buffer, sum);
			c_buf(buffer);
			sum = 0;
		}
		if (len + sign_pos > 1024)
		{
			write(STDOUT_FILENO, en->name, sign_pos);
			write(STDOUT_FILENO, "=", 1);
			write(STDOUT_FILENO, en->value, len);
			en = en->next;
		}
	}
	write(STDOUT_FILENO, buffer, sum);
	free(buffer);
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
 * @m_v: general struct
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
