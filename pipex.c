#include	"pipex.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>

char	*find_cmd_path(char *cmd, char *envp[])
{
	size_t	i;
	int	access_check;
	char	**path_arr;

	i = 0;
	access_check = 1;
	cmd = ft_strjoin("/", cmd);
	while (!find_path_env(envp[i]))
		i++;
	path_arr = ft_split(envp[i] + 5, ':');
	i = 0;
	while (access_check != 0 && path_arr[i] != '\0')
	{
		path_arr[i] = ft_strjoin_free(path_arr[i], cmd);
		access_check = access(path_arr[i], F_OK);
		if (access_check == -1)
			i++;
	}
	return (path_arr[i]);
}

void	pipex_process(int *pipefd, char *cmd, char *envp[])
{
	char	*cmd_path;
	char	**arg_arr;

	arg_arr = ft_split(cmd, ' ');
	cmd_path = find_cmd_path(arg_arr[0], envp);
	execve(cmd_path, arg_arr, envp);
}

int	main(int argc, char *argv[], char *envp[])
{
	int	id;
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		return (-1);
	if (argc > 2)
		id = fork();
	if (id == 0)
	{
		close(pipefd[0]);
		pipex_process(&pipefd[1], argv[1], envp);
	}
	else
	{
		close(pipefd[1]);
		wait(NULL);
		pipex_process(&pipefd[0], argv[2], envp);
	}
	return (0);
}
