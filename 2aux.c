#include "shell.h"
/**
 * _strcmp - check the code for Holberton School students.
 * @s1: variable to compare
 * @s2: variable to compare
 * Return: Always 0.
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

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
 * c_buf - clear buffer
 * @buff: buffer
 */
void c_buf(char *buff)
{
	int i = 0;

	while (i < 4096)
		buff[i] = '\0', i++;
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
 * clear_paths - free paths when its refering to working directory
 * @paths: pointer to a pointer of strings
 */
void clear_paths(char **paths)
{
	int i;

	for (i = 0; paths[i]; i++)
		free(paths[i]);
}
