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
