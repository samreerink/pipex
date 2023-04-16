#include	"pipex.h"
#include	<stdio.h>
#include	<stdlib.h>

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_free(char *s1, char *s2);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);

char	*find_cmd_path(char *cmd, char *envp[])
{
	size_t	i;
	char	**path_arr;

	i = 0;
	cmd = ft_strjoin("/", cmd);
	while (!find_path_env(envp[i]))
		i++;
	path_arr = ft_split(envp[i] + 5, ':');
	i = 0;
	while (path_arr[i] != '\0')
	{
		printf("%s\n", path_arr[i]);
		path_arr[i] = ft_strjoin_free(path_arr[i], cmd);
		printf("%s\n", path_arr[i]);
		i++;
	}
	return ("Hoi");
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*cmd_path;

	cmd_path = find_cmd_path(argv[1], envp);
	printf("%s\n", cmd_path);
	return (0);
}
