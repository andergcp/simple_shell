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
	int i = 0, len;

	len = _strlen(s1);
	if (len != _strlen(s2))
		return (1);
	while (s1[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
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
		i++;
	i++;

	p = malloc(sizeof(char) * i);

	if (p != NULL)
	{
		do {
			p[j] = str[j];
			j++;
		} while (str[j]);
		p[j] = '\0';
		return (p);
	}
	return (NULL);
}
/**
 * _strcpy - Print the length string.
 * @dest: Variable to change.
 * @src: Variable.
 * Return: None;
 */
void _strcpy(char *dest, char *src)
{
	char *a = dest;

	while (*src != '\0')
	{
		*a = *src;
		a += 1;
		src += 1;
	}
	*a = '\0';
}
