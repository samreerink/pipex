/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                           :+:    :+:             */
/*                                                     +:+                    */
/*   By: sreerink <sreerink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 21:21:12 by sreerink      #+#    #+#                 */
/*   Updated: 2024/01/09 20:47:17 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_process(char *cmd, char *envp[], t_pipex *pipex)
{
	pipex->arg_arr = ft_split(cmd, ' ');
	if (!pipex->arg_arr)
		error_exit("ft_split", EXIT_FAILURE, pipex);
	find_path_env(pipex, envp);
	if (pipex->path_arr == NULL)
		check_local(pipex);
	if (pipex->path_arr != NULL)
		find_cmd_path(pipex);
	execve(pipex->cmd_path, pipex->arg_arr, envp);
	error_exit(pipex->arg_arr[0], EXIT_FAILURE, pipex);
}

void	first_child(int pipefd[], char *argv[], char *envp[], t_pipex *pipex)
{
	int	file;

	close(pipefd[0]);
	file = open(argv[1], O_RDONLY);
	if (file == -1)
		error_exit(argv[1], EXIT_FAILURE, pipex);
	if (dup2(file, STDIN_FILENO) == -1)
		error_exit("dup2", EXIT_FAILURE, pipex);
	close(file);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		error_exit("dup2", EXIT_FAILURE, pipex);
	close(pipefd[1]);
	pipex_process(argv[2], envp, pipex);
}

void	second_child(int pipefd[], char *argv[], char *envp[], t_pipex *pipex)
{
	int	file;

	close(pipefd[1]);
	file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file == -1)
		error_exit(argv[4], EXIT_FAILURE, pipex);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		error_exit("dup2", EXIT_FAILURE, pipex);
	close(pipefd[0]);
	if (dup2(file, STDOUT_FILENO) == -1)
		error_exit("dup2", EXIT_FAILURE, pipex);
	close(file);
	pipex_process(argv[3], envp, pipex);
}

void	pre_pipex_process(char *argv[], char *envp[], t_pipex *pipex)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		error_exit("pipe", EXIT_FAILURE, pipex);
	pipex->pid1 = fork();
	if (pipex->pid1 == -1)
		error_exit("fork", EXIT_FAILURE, pipex);
	if (pipex->pid1 == 0)
		first_child(pipefd, argv, envp, pipex);
	pipex->pid2 = fork();
	if (pipex->pid2 == -1)
		error_exit("fork", EXIT_FAILURE, pipex);
	if (pipex->pid2 == 0)
		second_child(pipefd, argv, envp, pipex);
	close(pipefd[0]);
	close(pipefd[1]);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	*pipex;
	int		status;

	if (argc != 5)
	{
		write(STDERR_FILENO, "Invalid amount of arguments\n", 28);
		error_exit(NULL, EXIT_FAILURE, NULL);
	}
	pipex = ft_calloc(sizeof(t_pipex), 1);
	if (!pipex)
		error_exit("ft_calloc", EXIT_FAILURE, NULL);
	pipex->arg_arr = NULL;
	pipex->path_arr = NULL;
	pipex->cmd_path = NULL;
	pre_pipex_process(argv, envp, pipex);
	waitpid(pipex->pid1, NULL, 0);
	waitpid(pipex->pid2, &status, 0);
	free_pipex(pipex);
	return (WEXITSTATUS(status));
}
