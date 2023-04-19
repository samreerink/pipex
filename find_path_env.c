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

size_t	find_path_env(char *str, char *to_find)
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
