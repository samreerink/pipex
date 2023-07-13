#include	"pipex.h"

char	*find_cmd_path(char *cmd, char *envp[])
{
	size_t	i;
	int	access_check;
	char	**path_arr;

	i = 0;
	access_check = 1;
	cmd = ft_strjoin("/", cmd);
	//check strjoin
	while (!find_path_env(envp[i], "PATH="))
		i++;
	//when path env is not found
	path_arr = ft_split(envp[i] + 5, ':');
	i = 0;
	while (access_check != 0 && *path_arr[i] != '\0')
	{
		path_arr[i] = ft_strjoin_free(path_arr[i], cmd);
		access_check = access(path_arr[i], F_OK);
		if (access_check == -1)
			i++;
		//free path_arr
	}
	return (path_arr[i]);
}

void	pipex_process(char *cmd, char *envp[])
{
	char	*cmd_path;
	char	**arg_arr;

	arg_arr = ft_split(cmd, ' ');
	cmd_path = find_cmd_path(arg_arr[0], envp);
	if (execve(cmd_path, arg_arr, envp) == -1)
		error_exit(arg_arr[0], 1);
}

void	child_process(int pipefd[], char *argv[], char *envp[])
{
	int	file;

	close(pipefd[0]);
	file = open(argv[1], O_RDONLY);
	if (file == -1)
		error_exit("open in child process", 1);
	if (dup2(file, STDIN_FILENO) == -1)
		error_exit("dup2 in child process", 1);
	close(file);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		error_exit("dup2 in child process", 1);
	close(pipefd[1]);
	pipex_process(argv[2], envp);
}

void	parent_process(int pipefd[], char *argv[], char *envp[])
{
	int	file;

	close(pipefd[1]);
	file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file == -1)
		error_exit("open in parent process", 1);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		error_exit("dup2 in parent process", 1);
	close(pipefd[0]);
	if (dup2(file, STDOUT_FILENO) == -1)
		error_exit("dup2 in parent process", 1);
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
		error_exit("pipe", 1);
	id = fork();
	if (id == -1)
		error_exit("fork", 1);
	if (id == 0)
		child_process(pipefd, argv, envp);
	else
		parent_process(pipefd, argv, envp);
	return (0);
}
