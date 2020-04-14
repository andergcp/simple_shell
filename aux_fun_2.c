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
		Fnum[len -1] = (num % 10) + 48;
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
	while(buff[i])
		buff[i] = '\0', i++;
}
/**
 *
 *
 *
 */
void reset_path (char *aux_path)
{
	int i = 0;	

	while (aux_path[i])
	{
		if ((*(aux_path + i + 1) != '/') && (*(aux_path + i) == '\0'))
			break;
		if (*(aux_path + i) == '\0')
			*(aux_path + i) = ':';
		i++;
	}
}
void clear_paths(char **paths)
{
	int i;
	char *pwd = malloc(512);
	for (i = 0; paths[i]; i++)
	{
		if (_strcmp(paths[i], getcwd(pwd, 512)) == 0)
			free(paths[i]);
	}
	free(pwd);
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
