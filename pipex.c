#include	"pipex.h"

void	pipex_process(char *cmd, char *envp[])
{
	p_arr	arr;
	char	*cmd_path;

	arr.arg_arr = ft_split(cmd, ' ');
	if (!arr.arg_arr)
		error_exit("ft_split failed", 1, NULL);
	find_path_env(&arr, envp);
	cmd_path = find_cmd_path(&arr);
	if (cmd_path == NULL)
		cmd_path = arr.arg_arr[0];
	if (execve(cmd_path, arr.arg_arr, envp) == -1)
	{
		free(cmd_path);
		error_exit(arr.arg_arr[0], 1, &arr);
	}
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
		return (write(STDERR_FILENO, "Invalid amount of arguments, has to be 5\n", 41));
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
