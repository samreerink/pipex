#include	"pipex.h"

void	free_array(char *array[])
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

void	error_exit(char *error_msg, int status, t_pipex *pipex)
{
	if (pipex)
	{
		free_array(pipex->arg_arr);
		free_array(pipex->path_arr);
		free(pipex->cmd_path);
		free(pipex);
	}
	if (error_msg)
		perror(error_msg);
	exit(status);
}
