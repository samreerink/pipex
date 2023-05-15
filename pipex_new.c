#include	"pipex.h"

typedef struct pipex_struct {
	int	id;
	int	file;
	int	pipefd[2];
}	pipex_s;

void	pipex(char *argv[], char *envp[])
{
	pipex_s	pipex;

	if (pipe(pipex->pipefd) == -1)
		perror(NULL);
	pipex->id = fork();
	if (pipex->id == -1)
		perror(NULL);

}

int	main(int argc, char *argv[], char *envp[])
{
	if (argc != 5)
	{
		write(1, "Error: needs exactly 5 argumenst\n", 33);
		return (1);
	}
	pipex(argv, envp);
	return (0);
}
