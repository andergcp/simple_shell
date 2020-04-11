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
	return (0);
}
int comm_his(variables *m_v)
{
	return (0);
}
