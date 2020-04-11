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
/**
 *
 *
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
		Fnum[len -1] = (num % 10) + 48;
		num /= 10;
		len--;
	}
	return (Fnum);
}
/**
 * error_msg - print error message
 * @m_v: General struct
 * @msg: message to print
 */
void error_msg(variables *m_v, char *msg)
{
	char *buffer = malloc(512), *ptr = NULL;
	int len = 0, sum = 0, a = m_v->prompt_n;

	len = _strlen(m_v->argv[0]);
	sum += len, len = 1;
	_strcpy(buffer, m_v->argv[0]);
	_strcpy((buffer + sum), ": ");
	sum += 2;
	while (a / 10 != 0)
		a /= 10, len++;
	ptr = _itoa(m_v->prompt_n);
	_strcpy((buffer + sum), ptr);
	sum += len;
	_strcpy((buffer + sum), ": ");
	sum += 2;
	len = _strlen(m_v->args[0]);
	_strcpy((buffer + sum), m_v->args[0]);
	sum += len;
	_strcpy((buffer + sum), ": ");
	sum += 2;
	len = _strlen(msg);
	_strcpy((buffer + sum), msg);
	sum += len;
	buffer[sum] = '\n', sum++;
	write(STDERR_FILENO, buffer, sum);
	free(buffer);
	free(ptr);
}
