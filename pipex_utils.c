/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_path_env.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sreerink <sreerink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 02:47:12 by sreerink      #+#    #+#                 */
/*   Updated: 2023/04/18 02:48:01 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include	"pipex.h"

void	find_path_env(t_pipex *pipex, char *envp[])
{
	size_t	i;

	i = 0;
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
		error_exit("ft_split failed", 1, pipex);
}

void	check_local(t_pipex *pipex)
{
	if (access(pipex->arg_arr[0], F_OK) == 0)
	{
		pipex->cmd_path = pipex->arg_arr[0];
		return ;
	}
	error_exit(pipex->arg_arr[0], 127, pipex);
}

void	find_cmd_path(t_pipex *pipex)
{
	size_t	i;
	int	access_check;
	char	*cmd;

	i = 0;
	access_check = 1;
	cmd = ft_strjoin("/", pipex->arg_arr[0]);
	if (!cmd)
		error_exit("ft_strjoin failed", 1, pipex);
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
