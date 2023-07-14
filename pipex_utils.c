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

void	error_exit(char *error_msg, int status, char *to_free[])
{
	if (to_free)
	{
		//free array
	}
	perror(error_msg);
	exit(status);
}

char	**find_path_env(char *envp[])
{
	size_t	i;
	char	**path_arr;

	i = 0;
	while (!search_str(envp[i], "PATH="))
	{
		i++;
		if (!envp[i])
			return (NULL);
	}
	path_arr = ft_split(envp[i] + 5, ':');
	if (!path_arr)
		error_exit("ft_split failed", 1, NULL);
	return (path_arr);
}

char	*check_local(char *cmd)
{
	if (access(cmd, F_OK) == 0)
		return (NULL);
	error_exit(cmd, 127);
}

char	*find_cmd_path(char *cmd, char *path_arr[], envp)
{
	size_t	i;
	int	access_check;
	char	cmd_slash;

	i = 0;
	access_check = 1;
	if (!path_arr)
	{
		cmd = check_local(cmd);
		return (cmd);
	}
	cmd_slash = ft_strjoin("/", cmd);
	if (!cmd_slash)
		error_exit("ft_strjoin failed", 1, &path_arr);
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
