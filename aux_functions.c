#include "shell.h"
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
