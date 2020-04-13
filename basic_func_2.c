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
 
void reset_path (char *aux_path)
{
	int i = 0;	

	while (aux_path[i])
	{
		//if ((*(aux_path + i + 1) != '/') && (*(aux_path + i) == '\0'))
		//	break;
		if (*(aux_path + i) == '\0')
			*(aux_path + i) = ':';
		i++;
	}
	}*/
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
	DIR *dir = NULL;
	struct stat aux_stat;

	if (!buffer)
		return (NULL);
	dup_path = _strdup(aux_path);
	paths = _strtok_path(dup_path);
	if (!paths)
		return (NULL);
	size = 0;
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
		if ((dir = opendir(buffer)) == NULL)
			if (stat(buffer, &aux_stat) != -1)
				if (access(buffer, X_OK) == 0)
					return (free(paths), free(dup_path), buffer);
		size++;
		c_buf(buffer);
	}
	free(dup_path), size = 0;
	free(paths), free(buffer);;
	return (NULL);
}
