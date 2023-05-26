/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sreerink <sreerink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 02:47:42 by sreerink      #+#    #+#                 */
/*   Updated: 2023/04/18 02:47:55 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include	"pipex.h"

char	*find_cmd_path(char *cmd, char *envp[])
{
	size_t	i;
	int	access_check;
	char	**path_arr;

	i = 0;
	access_check = 1;
	cmd = ft_strjoin("/", cmd);
	while (!find_path_env(envp[i], "PATH="))
		i++;
	path_arr = ft_split(envp[i] + 5, ':');
	i = 0;
	while (access_check != 0 && *path_arr[i] != '\0')
	{
		path_arr[i] = ft_strjoin_free(path_arr[i], cmd);
		access_check = access(path_arr[i], F_OK);
		if (access_check == -1)
			i++;
	}
	return (path_arr[i]);
}

void	pipex_process(char *cmd, char *envp[])
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
	int	file;
	int	pipefd[2];

	id = 0;
	if (argc != 5)
		return (printf("Need 5 arguments\n"), -1);
	if (pipe(pipefd) == -1)
		return (-1);
	id = fork();
	if (id == 0)
	{
		close(pipefd[0]);
		file = open(argv[1], O_RDONLY);
		if (file == -1)
			return (perror(argv[1]), -1);
		dup2(file, STDIN_FILENO);
		close(file);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		pipex_process(argv[2], envp);
	}
	else
	{
		close(pipefd[1]);
		file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC);
		if (file == -1)
			return (perror(argv[4]), -1);
		dup2(pipefd[0], STDIN_FILENO);
		dup2(file, STDOUT_FILENO);
		close(pipefd[1]);
		pipex_process(argv[3], envp);
	}
	return (0);
}
