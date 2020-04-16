#include "shell.h"
/**
 * _itoa - covert integer to char
 * @num: number to convert
 * Return: string
 */
char *_itoa(int num)
{
	int len = 1, a = num;
	char *Fnum = malloc(4);

	while (a / 10 != 0)
		a /= 10, len++;
	Fnum[len] = '\0';
	while (len > 0)
	{
		Fnum[len - 1] = (num % 10) + 48;
		num /= 10;
		len--;
	}
	return (Fnum);
}
/**
 * c_buf - clear buffer
 * @buff: buffer
 */
void c_buf(char *buff)
{
	int i = 0;

	while (buff[i])
		buff[i] = '\0', i++;
}
/**
 * clear_paths - free paths when its refering to working directory
 * @paths: pointer to a pointer of strings
 */
void clear_paths(char **paths)
{
	int i;

	for (i = 0; paths[i]; i++)
		free(paths[i]);
}
/**
 * _atoi - Casting of a string to integer.
 * @s: Variable to change.
 * Return: Integer;
 */
int _atoi(char *s)
{
	unsigned int sum = 0;
	int i = 0;

	if (!s)
		return (-1);
	while (s[i] != '\0')
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			sum = sum * 10;
			sum += s[i] - '0';
		}
		else
			return (-1);
		i++;
	}
	return (sum);
}
/**
 * _envtoarray - Converts linke list to double pointer
 * @vars: General variables
 * Return: Returns -1 if failed;
 */
char **tr_env(variables *m_v)
{
	char **env;
	int i;
	env_v *tmp = m_v->p_env;

	for (i = 0; tmp; i++)
		tmp = tmp->next;
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	tmp = m_v->p_env;
	for (i = 0; tmp; i++)
	{
		env[i] = malloc(2048);
		env[i][0] = '\0';
		_strcat(env[i], tmp->name);
		_strcat(env[i], "=");
		_strcat(env[i], tmp->value);
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}
