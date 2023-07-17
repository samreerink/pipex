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

void	error_exit(char *error_msg, int status, p_arr *arr)
{
	if (arr->arg_arr)
		free_array(&arr->arg_arr);
	if (arr->path_arr)
		free_array(&arr->path_arr);
	perror(error_msg);
	exit(status);
}

void	find_path_env(p_arr *arr, char *envp[])
{
	size_t	i;

	i = 0;
	while (!search_str(envp[i], "PATH="))
	{
		i++;
		if (!envp[i])
			return (NULL);
	}
	arr->path_arr = ft_split(envp[i] + 5, ':');
	if (!path_arr)
		error_exit("ft_split failed", 1, &arr);
}

char	*check_local(char *cmd, p_arr *arr)
{
	if (access(cmd, F_OK) == 0)
		return (NULL);
	error_exit(cmd, 127, &arr);
}

char	*find_cmd_path(p_arr *arr)
{
	size_t	i;
	int	access_check;
	char	*cmd;
	char	*cmd_path;

	i = 0;
	access_check = 1;
	if (!arr->path_arr)
		return (check_local(arr->arg_arr[0], &arr));
	cmd = ft_strjoin("/", arr->arg_arr[0]);
	if (!cmd)
		error_exit("ft_strjoin failed", 1, &arr);
	while (access_check != 0 && arr->path_arr[i])
	{
		arr->path_arr[i] = ft_strjoin_free(arr->path_arr[i], cmd);
		access_check = access(arr->path_arr[i], F_OK);
		if (access_check == -1)
			i++;
	}
	cmd_path = ft_strdup(arr->path_arr[i]);
	free(cmd);
	free_array(arr->path_arr);
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
