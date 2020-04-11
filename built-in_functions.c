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
	return (0);
}
int comm_ex(variables *m_v)
{

	if (m_v->args[1] != NULL)
	{
		free(m_v->args);
		free(m_v->ptr);
		free(m_v);
		exit(0);
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
