#include "shell.h"
int comm_cd(variables *m_v)
{
	char pwd[4096];
	int len;

	if (m_v->args[1] == NULL) 
	{
		_strcpy(pwd, get_env(m_v, "HOME"));
		if (chdir(pwd) != 0)
		{
			perror("error1");
			return (0);
		}
		set_env(m_v, "OLDPWD", get_env(m_v, "PWD"));
		getcwd(pwd, 4096);
		set_env(m_v, "PWD", pwd);
		len = _strlen(pwd);
		pwd[len] = '\n';
		write(STDOUT_FILENO, pwd, len + 1);
		return (0);
	}
	else if (_strcmp(m_v->args[1], "-") == 0)
	{
		_strcpy(pwd, get_env(m_v, "OLDPWD"));
		if (!pwd)
			return (error_msg(m_v, "theres no OLDPWD"), 0);
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
		{
			_strcpy(pwd, "can't cd to ");
			_strcat(pwd, m_v->args[1]);
			error_msg(m_v, pwd);
			return (0);
		}
		set_env(m_v, "OLDPWD", get_env(m_v, "PWD"));
		getcwd(pwd, 4096);
		set_env(m_v, "PWD", pwd);
		len = _strlen(pwd);
		pwd[len] = '\n';
		write(STDOUT_FILENO, pwd, len + 1);
	}
	return (0);
}
int comm_he(variables *m_v)
{
	int fd, num_bytes, i = 0;
	char *buf = malloc(1024);

	if (!buf)
		return (error_msg(m_v, "No allocate buf"), 0);

	if (m_v->args[0] != NULL && m_v->args[1] == NULL)
	{

		fd = open("builtin.txt", O_RDONLY);
		
		do
		{
			num_bytes = read(fd, buf, 1024);
			
			if (num_bytes == -1)
				return (error_msg(m_v, "No file opened"), free(buf), close(fd), 0);			
			
			write (STDOUT_FILENO, buf, num_bytes);
		} while (num_bytes > 0);

	}
	if (m_v->args[0] != NULL && m_v->args[1] != NULL)
	{
		while (m_v->diccio[i].command)
		{
			if (_strcmp(m_v->diccio[i].command, m_v->args[1]) == 0)
			{
				fd = open(m_v->diccio[i].help, O_RDONLY);

                		do
                		{
                        		num_bytes = read(fd, buf, 1024);

                        		if (num_bytes == -1)
                                		return (error_msg(m_v, "No file opened"), free(buf), close(fd), 0);

                        		write (STDOUT_FILENO, buf, num_bytes);
                		} while (num_bytes > 0);


			}
			
			i++;
		}
		return (error_msg(m_v, "no help topics match this string"), free(buf), close(fd), 0);
	}
	
	close(fd);
	free(buf);
	return (0);
}
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
}
int comm_en(variables *m_v)
{
	
	print_env(m_v);
        /*char *buffer = malloc(1024);
	int i = 0, sum = 0, len;
	if (!buffer)
		return (-1);
	while (m_v->env[i])
	{
		len = _strlen(m_v->env[i]);
                //Se suma uno para tener en cuenta el salto de linea
		if (len + sum + 1 < 1024)
		{
			_strcpy((buffer + sum), m_v->env[i]);
			sum += len;
			buffer[sum] = '\n';
			sum++, i++;
		}
		else
		{
			write(STDOUT_FILENO, buffer, sum);
			c_buf(buffer);
			sum = 0;
		}
		if (len > 1024)
			write(STDOUT_FILENO, m_v->env[i], len), i++;
	}
	write(STDOUT_FILENO, buffer, sum);
	free(buffer);
	return (0);
	*/
}
int comm_his(variables *m_v)
{
	return (0);
}
