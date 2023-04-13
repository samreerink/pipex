#include	<stdio.h>
#include	<unistd.h>

size_t	find_path_env(char *str);

char	*find_cmd_path(char *envp[])
{
	size_t	i;

	i = 0;
	while (!find_path_env(envp[i]))
		i++;
	return (envp[i]);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*cmd_path;

	cmd_path = find_cmd_path(envp);
	printf("%s\n", cmd_path);
	return (0);
}
