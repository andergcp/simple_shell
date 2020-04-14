#include "shell.h"
int comm_cd(variables *m_v)
{
	if (m_v->args[1] == NULL) {
		write(STDOUT_FILENO, "expected argument to \n", 22);
	} else {
		if (chdir(m_v->args[1]) != 0) {
			perror(m_v->argv[0]);
		}
	}
	return (0);
}
int comm_he(variables *m_v)
{
	inside *ptr = dic_command();
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
		while (ptr[i].command)
		{
			if (_strcmp(ptr[i].command, m_v->args[1]) == 0)
			{
				fd = open(ptr[i].help, O_RDONLY);

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
		free(m_v);
		exit(m_v->status);
	}
	else if (m_v->args[1] != NULL && m_v->args[0] != NULL)
	{
		i = _atoi(m_v->args[1]);
		if (i <= -1)
			return (-1);
		free(m_v->args);
                free(m_v->ptr);
                free(m_v);
                exit(i);
	}

}
int comm_en(variables *m_v)
{
	char *buffer = malloc(1024);
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
}
int comm_his(variables *m_v)
{
	return (0);
}
