#include "shell.h"
int comm_cd(variables *m_v)
{
	return (0);
}
int comm_he(variables *m_v)
{
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
		exit(0);
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
	return (0);
}
int comm_his(variables *m_v)
{
	return (0);
}
