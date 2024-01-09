/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_error.c                                     :+:    :+:             */
/*                                                     +:+                    */
/*   By: sreerink <sreerink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 21:20:45 by sreerink      #+#    #+#                 */
/*   Updated: 2024/01/09 18:41:34 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_pipex(t_pipex *pipex)
{
	free_array(pipex->arg_arr);
	free_array(pipex->path_arr);
	free(pipex->cmd_path);
	free(pipex);
}

void	free_array(char **array)
{
	size_t	i;

	i = 0;
	if (!array)
		return ;
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
	if (status == 127)
	{
		write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
		write(STDERR_FILENO, ": command not found\n", 20);
	}
	else if (error_msg != NULL)
		perror(error_msg);
	if (pipex)
		free_pipex(pipex);
	exit(status);
}
