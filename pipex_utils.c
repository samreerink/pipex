/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_utils.c                                     :+:    :+:             */
/*                                                     +:+                    */
/*   By: sreerink <sreerink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 21:21:00 by sreerink      #+#    #+#                 */
/*   Updated: 2024/01/08 21:07:44 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_pipex(t_pipex *pipex)
{
	pipex = ft_calloc(sizeof(t_pipex), 1);
	if (!pipex)
		error_exit("ft_calloc", EXIT_FAILURE, NULL);
	pipex->arg_arr = NULL;
	pipex->path_arr = NULL;
	pipex->cmd_path = NULL;
}

void	find_path_env(t_pipex *pipex, char *envp[])
{
	size_t	i;

	i = 0;
	if (!pipex->arg_arr[0])
		error_exit(" ", 127, pipex);
	if (!envp)
		return ;
	while (!search_str(envp[i], "PATH="))
	{
		i++;
		if (!envp[i])
			return ;
	}
	pipex->path_arr = ft_split(envp[i] + 5, ':');
	if (!pipex->path_arr)
		error_exit("ft_split", EXIT_FAILURE, pipex);
}

void	check_local(t_pipex *pipex)
{
	if (access(pipex->arg_arr[0], F_OK) == 0)
	{
		if (access(pipex->arg_arr[0], X_OK) != 0)
			error_exit(pipex->arg_arr[0], 126, pipex);
		pipex->cmd_path = ft_strdup(pipex->arg_arr[0]);
		return ;
	}
	error_exit(pipex->arg_arr[0], 127, pipex);
}

void	find_cmd_path(t_pipex *pipex)
{
	size_t	i;
	int		access_check;
	char	*cmd;

	i = 0;
	access_check = 1;
	cmd = ft_strjoin("/", pipex->arg_arr[0]);
	if (!cmd)
		error_exit("ft_strjoin", EXIT_FAILURE, pipex);
	while (access_check != 0 && pipex->path_arr[i])
	{
		pipex->path_arr[i] = ft_strjoin_free(pipex->path_arr[i], cmd);
		access_check = access(pipex->path_arr[i], F_OK);
		if (access_check == -1)
			i++;
	}
	free(cmd);
	if (access_check == 0)
		pipex->cmd_path = ft_strdup(pipex->path_arr[i]);
	else
		check_local(pipex);
	free_array(pipex->path_arr);
	pipex->path_arr = NULL;
}

size_t	search_str(char *str, char *to_find)
{
	size_t	i;

	i = 0;
	while (str[i] == to_find[i])
	{
		i++;
		if (to_find[i] == '\0')
			return (1);
	}
	return (0);
}
