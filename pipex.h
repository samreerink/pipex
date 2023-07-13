/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sreerink <sreerink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 02:47:48 by sreerink      #+#    #+#                 */
/*   Updated: 2023/04/18 02:47:51 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

# include	<stdio.h>
# include	<stdlib.h>
# include	<unistd.h>
# include	<fcntl.h>
# include	<sys/types.h>
# include	<sys/wait.h>

void	error_exit(char *error_msg, int status);

size_t	find_path_env(char *str, char *to_find);

char	**ft_split(char const *s, char c);

char	*ft_strjoin(char const *s1, char const *s2);

char	*ft_strjoin_free(char *s1, char *s2);

void	*ft_calloc(size_t count, size_t size);

char	*ft_strdup(const char *s1);

#endif
