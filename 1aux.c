#include "shell.h"
/**
 * error_msg - print error message
 * @m_v: General struct
 * @msg: message to print
 */
void error_msg(vari *m_v, char *msg)
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
