/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sreerink <sreerink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 21:20:45 by sreerink      #+#    #+#                 */
/*   Updated: 2023/07/21 21:20:46 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include	"pipex.h"

void	free_array(char *array[])
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

void	error_exit(char *error_msg, int status, t_pipex *pipex)
{
	extern int	errno;

	if (errno == EACCES)
		status = 126;
	if (error_msg)
		perror(error_msg);
	if (pipex)
	{
		free_array(pipex->arg_arr);
		if (pipex->path_arr)
			free_array(pipex->path_arr);
		free(pipex->cmd_path);
		free(pipex);
	}
	exit(status);
}
