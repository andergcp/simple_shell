#include "shell.h"
/**
 * _strlen - Print the length string.
 * @s: Variable to change the value.
 * Return: None;
 */
int _strlen(char *s)
{
	int contador;

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
	int resultado, i = 0;

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
	return (resultado);
}
/**
 * get_path - get path line
 * @env: environment
 * Return: pointer that point to path line
 */
char *get_path(char **env)
{
	int i;

	for (i = 0; env[i]; i++)
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' &&
		    env[i][2] == 'T' && env[i][3] == 'H')
			return (env[i] + 5);

	}
	return (NULL);
}
