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
