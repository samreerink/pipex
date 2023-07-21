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

void	error_exit(char *error_msg, int status, t_pipex *pipex)
{
	if (pipex)
	{
		free_array(pipex->arg_arr);
		free_array(pipex->path_arr);
		free(pipex);
	}
	if (error_msg)
		perror(error_msg);
	exit(status);
}

void	find_path_env(t_pipex *pipex, char *envp[])
{
	size_t	i;

	i = 0;
	while (!search_str(envp[i], "PATH="))
	{
		i++;
		if (!envp[i])
			return (NULL);
	}
	pipex->path_arr = ft_split(envp[i] + 5, ':');
	if (!path_arr)
		error_exit("ft_split failed", 1, pipex);
}

char	*check_local(char *cmd, t_pipex *pipex)
{
	if (access(cmd, F_OK) == 0)
		return (NULL);
	error_exit(cmd, 127, pipex);
}

char	*find_cmd_path(t_pipex *pipex)
{
	size_t	i;
	int	access_check;
	char	*cmd;
	char	*cmd_path;

	i = 0;
	access_check = 1;
	if (!pipex->path_arr)
		return (check_local(pipex->arg_arr[0], pipex));
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
	cmd_path = ft_strdup(pipex->path_arr[i]);
	free(cmd);
	free_array(pipex->path_arr);
	return (cmd_path);
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
