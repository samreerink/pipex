/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                           :+:    :+:             */
/*                                                     +:+                    */
/*   By: sreerink <sreerink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 02:47:48 by sreerink      #+#    #+#                 */
/*   Updated: 2024/01/08 21:10:50 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "Libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_pipex
{
	pid_t	id;
	char	**arg_arr;
	char	**path_arr;
	char	*cmd_path;
}	t_pipex;

void	error_exit(char *error_msg, int status, t_pipex *pipex);

void	init_pipex(t_pipex *pipex);

void	free_array(char **array);

void	find_path_env(t_pipex *pipex, char *envp[]);

void	check_local(t_pipex *pipex);

void	find_cmd_path(t_pipex *pipex);

size_t	search_str(char *str, char *to_find);

#endif
