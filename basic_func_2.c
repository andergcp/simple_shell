#include "shell.h"
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

	while (1)
	{
		if ((*(aux_path + i) == '\0') && (*(aux_path + i + 1) != '/'))
			break;
		if (*(aux_path + i) == '\0')
			*(aux_path + i) = ':';
		i++;
	}
}
/**
 * handle_path
 *
 *
 */
char *handle_path(variables *m_v)
{
	char *aux_path = get_path(m_v);
	char *dup_path = NULL;
	char *str = NULL;
	char *buffer = malloc(1024);
	char **paths = NULL;
	int i = 0, size = 1, c_buff = 0;
	struct stat aux_stat;

	if (!buffer)
		return (NULL);

	dup_path = _strdup(aux_path);
	while (aux_path[i])
	{
		if (aux_path[i] == ':')
			size++;
		i++;
	}

	paths = malloc(sizeof(char *) * (size + 1)), size = 0;
	if (!paths)
		return (NULL);
	str = strtok(dup_path, ":");
	while (str)
	{
		paths[size] = str;
		str = strtok(NULL, ":");
		size++;
	}
	paths[size] = NULL, size = 0;
        // concatenate path with command and validate it
	while (paths[size])
	{
		i = 0, c_buff = 0;
		while (paths[size][i])
			buffer[c_buff] = paths[size][i], i++, c_buff++;
		buffer[c_buff] = '/', c_buff++;
		i = 0;
		while (m_v->args[0][i])
			buffer[c_buff] = m_v->args[0][i], i++, c_buff++;
		buffer[c_buff] = '\0';
		if (stat(buffer, &aux_stat) != -1)
			if (access(buffer, X_OK) == 0)
				return (free(paths), free(dup_path), reset_path(aux_path), buffer);
		size++;
		c_buf(buffer);
	}
	reset_path(aux_path);
	free(dup_path);
	free(paths);
	free(buffer);
	return (NULL);
}