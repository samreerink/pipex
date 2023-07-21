#include	"pipex.h"

void	pipex_process(char *cmd, char *envp[])
{
	t_pipex	*pipex;

	pipex = ft_calloc(sizeof(t_pipex), 1);
	if (!pipex)
		error_exit("ft_calloc failed", 1, NULL);
	pipex->path_arr = NULL;
	pipex->cmd_path = NULL;
	pipex->arg_arr = ft_split(cmd, ' ');
	if (!pipex->arg_arr)
		error_exit("ft_split failed", 1, pipex);
	find_path_env(pipex, envp);
	if (pipex->path_arr == NULL)
		check_local(pipex);
	if (pipex->path_arr != NULL)
		find_cmd_path(pipex);
	if (execve(pipex->cmd_path, pipex->arg_arr, envp) == -1)
		error_exit(pipex->arg_arr[0], 1, pipex);
}

void	child_process(int pipefd[], char *argv[], char *envp[])
{
	int	file;

	close(pipefd[0]);
	file = open(argv[1], O_RDONLY);
	if (file == -1)
		error_exit("open in child process", 1, NULL);
	if (dup2(file, STDIN_FILENO) == -1)
		error_exit("dup2 in child process", 1, NULL);
	close(file);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		error_exit("dup2 in child process", 1, NULL);
	close(pipefd[1]);
	pipex_process(argv[2], envp);
}

void	parent_process(int pipefd[], char *argv[], char *envp[])
{
	int	file;

	close(pipefd[1]);
	file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file == -1)
		error_exit("open in parent process", 1, NULL);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		error_exit("dup2 in parent process", 1, NULL);
	close(pipefd[0]);
	if (dup2(file, STDOUT_FILENO) == -1)
		error_exit("dup2 in parent process", 1, NULL);
	close(file);
	pipex_process(argv[3], envp);
}

int	main(int argc, char *argv[], char *envp[])
{
	int	id;
	int	pipefd[2];

	id = 0;
	if (argc != 5)
	{
		write(STDERR_FILENO, "Invalid amount of arguments\n", 28);
		error_exit(NULL, 1, NULL);
	}
	if (pipe(pipefd) == -1)
		error_exit("pipe", 1, NULL);
	id = fork();
	if (id == -1)
		error_exit("fork", 1, NULL);
	if (id == 0)
		child_process(pipefd, argv, envp);
	else
		parent_process(pipefd, argv, envp);
	return (0);
}
