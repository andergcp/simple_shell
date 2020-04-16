#include "shell.h"
/**
 * comm_cd - changes working directory
 * @m_v: structure of variables used in the program
 * Return: When success 0
 */
int comm_cd(variables *m_v)
{
	char pwd[4096];
	int len;

	if (m_v->args[1] == NULL)
	{
		_strcpy(pwd, get_env(m_v, "HOME"));
		if (chdir(pwd) != 0)
			return (error_msg(m_v, "Dir no found"), 0);
		set_env(m_v, "OLDPWD", get_env(m_v, "PWD"));
		getcwd(pwd, 4096);
		set_env(m_v, "PWD", pwd);
		len = _strlen(pwd);
		pwd[len] = '\n';
		return (write(STDOUT_FILENO, pwd, len + 1), 0);
	}
	else if (_strcmp(m_v->args[1], "-") == 0)
	{
		_strcpy(pwd, get_env(m_v, "OLDPWD"));
		if (chdir(get_env(m_v, "OLDPWD")) != 0)
			return (perror("error2"), 0);
		set_env(m_v, "OLDPWD", get_env(m_v, "PWD"));
		set_env(m_v, "PWD", pwd);
		len = _strlen(pwd);
		pwd[len] = '\n';
		write(STDOUT_FILENO, pwd, len + 1);
	}
	else
	{
		if (chdir(m_v->args[1]) != 0)
			return (_strcpy(pwd, "can't cd to "), _strcat(pwd, m_v->args[1]),
				error_msg(m_v, pwd), 0);
		set_env(m_v, "OLDPWD", get_env(m_v, "PWD"));
		getcwd(pwd, 4096);
		set_env(m_v, "PWD", pwd);
		len = _strlen(pwd), pwd[len] = '\n';
		write(STDOUT_FILENO, pwd, len + 1);
	}
	return (0);
}
/**
 * comm_he - Display built-in help files
 * @m_v: structure of variables used in the program
 * Return: When sucess 0
 */
int comm_he(variables *m_v)
{
	int fd, num_bytes, i = 0;
	char *buf = malloc(1024);

	if (!buf)
		return (error_msg(m_v, "No allocate buf"), 0);

	if (m_v->args[0] != NULL && m_v->args[1] == NULL)
	{
		fd = open("builtin.txt", O_RDONLY);
		do {
			num_bytes = read(fd, buf, 1024);
			if (num_bytes == -1)
				return (error_msg(m_v, "No file opened"), free(buf), close(fd), 0);
			write(STDOUT_FILENO, buf, num_bytes);
		} while (num_bytes > 0);
	}
	if (m_v->args[0] != NULL && m_v->args[1] != NULL)
	{
		while (m_v->diccio[i].command)
		{
			if (_strcmp(m_v->diccio[i].command, m_v->args[1]) == 0)
			{
				fd = open(m_v->diccio[i].help, O_RDONLY);
				do {
					num_bytes = read(fd, buf, 1024);
					if (num_bytes == -1)
						return (error_msg(m_v, "No file opened"), free(buf), close(fd), 0);
					write(STDOUT_FILENO, buf, num_bytes);
				} while (num_bytes > 0);
			}
			i++;
		}
		return (free(buf), error_msg(m_v, "no help topics match this string"), 0);
	}
	return (free(buf), 0);
}
/**
 * comm_ex - exits the program
 * @m_v: structure of variables used in the program
 * Return: When argumente is stablished return this integer,
 * if don't return the last status, when fails return -2
 */
int comm_ex(variables *m_v)
{
	int i;

	if (m_v->args[1] == NULL && m_v->args[0] != NULL)
	{
		free(m_v->args);
		free(m_v->ptr);
		free(m_v->diccio);
		clear_env(m_v);
		i = m_v->status;
		free(m_v);
		exit(i);
	}
	else if (m_v->args[1] != NULL && m_v->args[0] != NULL)
	{
		i = _atoi(m_v->args[1]);
		if (i <= -1)
		{
			error_msg(m_v, "Illegal number");
			m_v->status = 2;
			return (-2);
		}
		free(m_v->args);
		free(m_v->ptr);
		free(m_v->diccio);
		clear_env(m_v);
		free(m_v);
		exit(i);
	}
	return (0);
}
/**
 * comm_en - Prints environment variables
 * @m_v: structure of variables used in the program
 * Return: When success 0
 */
int comm_en(variables *m_v)
{
	char *buffer = malloc(1024);
	env_v *en = m_v->p_env;
	int sum = 0, len, sign_pos;

	if (!buffer)
		return (0);
	while (en)
	{
		len = _strlen(en->name);
		sign_pos = len;
		len = _strlen(en->value);
		if (len + sum + 1 < 1024)
		{
			_strcpy((buffer + sum), en->name);
			buffer[sign_pos + sum] = '=';
			sum += sign_pos + 1;
			_strcpy((buffer + sum), en->value);
			sum += len;
			buffer[sum] = '\n';
			buffer[sum + 1] = '\0';
			en = en->next, sum++;
		}
		else
		{
			write(STDOUT_FILENO, buffer, sum);
			c_buf(buffer);
			sum = 0;
		}
		if (len + sign_pos > 1024)
		{
			write(STDOUT_FILENO, en->name, sign_pos);
			write(STDOUT_FILENO, "=", 1);
			write(STDOUT_FILENO, en->value, len);
			en = en->next;
		}
	}
	write(STDOUT_FILENO, buffer, sum);
	free(buffer);
	return (0);
}
