#include	<stdio.h>

size_t	find_path_env(char *str)
{
	size_t	i;
	char	*path;

	i = 0;
	path = "PATH=";
	while (str[i] == path[i])
	{
		i++;
		if (path[i] == '\0')
			return (1);
	}
	return (0);
}
/*
size_t	pipex_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}*/
