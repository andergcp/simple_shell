#include "shell.h"
/**
 * _strlen - Print the length string.
 * @s: Variable to change the value.
 * Return: None;
 */
int _strlen(char *s)
{
	int contador = 0;

	while (s[contador] != '\0')
		contador++;
	return (contador);
}
/**
 * _strcat - concatenatestwo strings
 * @dest: pointer to a char
 * @src: pointer to a char
 * Return: dest
 **/

char *_strcat(char *dest, char *src)
{
	int i = _strlen(dest);
	int total_len = _strlen(src) + i;
	int counter = 0;

	while (i < total_len)
	{
		dest[i] = src[counter];
		counter++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/**
 * _strcmp - check the code for Holberton School students.
 * @s1: variable to compare
 * @s2: variable to compare
 * Return: Always 0.
 */
int _strcmp(char *s1, char *s2)
{
	int resultado, i = 0, len;

	len = _strlen(s1);
	if (_strlen(s2) == len)
	{
		while (s1[i] != '\0' && s2[i] != '\0')
		{
			resultado = s1[i] - s2[i];
			if (resultado == 0)
			{
				i++;
				continue;
			}
			else
				break;
		}
	}
	else
		resultado = 24;
	return (resultado);
}
/**
 * get_path - get path line
 * @env: environment
 * Return: pointer that point to path line
 */
char *get_path(variables *m_v)
{
	int i;

	for (i = 0; m_v->env[i]; i++)
	{
		if (m_v->env[i][0] == 'P' && m_v->env[i][1] == 'A' &&
		    m_v->env[i][2] == 'T' && m_v->env[i][3] == 'H')
			return ((m_v->env[i]) + 5);

	}
	return (NULL);
}

/**
 * *_strdup - returns a pointer to a newly allocated space in memory,
 * which contains a copy of the string given as a parameter.
 * @str: Ppinter to a char
 * Return: NULL if str is null, a pointer when successful.
 **/

char *_strdup(char *str)
{
	int i = 0, j = 0;
	char *p;

	while (str[i])
	{
		i++;
	}
	i++;

	p = malloc(sizeof(*p) * i);

	if (p != NULL)
	{
		do {
			p[j] = str[j];
			j++;
		} while (str[j]);
		p[j] = '\0';
		return (p);
	}
	else
		return (NULL);
	return (NULL);
}
