#include "shell.h"
/**
 * _atoi - Casting of a string to integer.
 * @s: Variable to change.
 * Return: Integer;
 */
int _atoi(char *s)
{
	unsigned int sum = 0;
	int i = 0;

	while (s[i] != '\0')
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			sum = sum * 10;
			sum += s[i] - '0';
		}
		else if (sum != 0)
				return (-1);
		i++;
	}
	return (sum);
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
