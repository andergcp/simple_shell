#include "shell.h"
/**
 * _strtok_path - 
 *
 *
 */
char **_strtok_path(char *ptr)
{
	char **paths = NULL, *ptr1 = malloc(512);
	int len, i = 0, j = 0, sizeP = 1;
	
	while (ptr[i])
	{
		if (ptr[i] == ':')
			sizeP++;
		i++;
	}
	paths = malloc(sizeof(char *) * (sizeP + 1)), i = 0;
	if (!paths)
		return (NULL);
	while (ptr[i])
	{
		if ((ptr[i] == ':') && (i == 0 || ptr[i - 1] == '\0' ||
					ptr[i + 1] == '\0'))
		{
			ptr[i] = '\0';
			getcwd(ptr1, sizeof(char) * 1024);
			paths[j] = ptr1;
			j++;
		}
		else if ((ptr[i] != ':') && (i == 0 || ptr[i - 1] == '\0'))
		{
			paths[j] = (ptr + i);
			j++;
		}
		else if (ptr[i] == ':')
			ptr[i] = '\0';
		i++;
	}
	paths[j] = NULL;
	return (paths);
}
