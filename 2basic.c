#include "shell.h"
/**
 * _strtok_line - split a string
 * @m_v: general struct
 * Return: double pointer to ptr tokenized
 */
void _strtok_line(vari *m_v)
{
	char *tmp = NULL;
	int index = 0, sizeP = 0;

	for (index = 0; m_v->ptr[index]; index++)
	{
		if ((m_v->ptr[index] != ' ' && m_v->ptr[index] != '\t'
		     && m_v->ptr[index] != '\n' && m_v->ptr[index] != ';') &&
		    (index == 0 || m_v->ptr[index - 1] == '\t' ||
		     m_v->ptr[index - 1] == ' '))
			sizeP++;
	}
	m_v->args = malloc(sizeof(char *) * (sizeP + 1));
	if (!m_v->args)
		return;
	tmp = strtok(m_v->ptr, " \t\n");
	for (index = 0; tmp; index++)
	{
		m_v->args[index] = tmp;
		tmp = strtok(NULL, " \t\n");
	}
	m_v->args[index] = NULL;
}
/**
 * _strtok_path - tokenize the PATH
 * @ptr: pointer to variable PATH
 * Return: pointer to array of strings with values of PATH
 */
char **_strtok_path(char *ptr)
{
	char **paths = NULL, *token;
	int i = 0, sizeP = 1;

	while (ptr[i])
	{
		if (ptr[i] == ':')
			sizeP++;
		i++;
	}
	paths = malloc(sizeof(char *) * (sizeP + 1));
	if (!paths)
		return (NULL);
	token = strtok(ptr, ":");
	for (i = 0; token; i++)
	{
		paths[i] = strdup(token);
		token = strtok(NULL, ":");
	}
	paths[i] = NULL;
	free(token);
	return (paths);
}
