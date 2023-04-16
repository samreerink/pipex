/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sreerink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/13 18:45:19 by sreerink      #+#    #+#                 */
/*   Updated: 2022/11/13 21:04:59 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s_copy;
	size_t	len;

	len = ft_strlen(s1) + 1;
	s_copy = malloc(sizeof(char) * len);
	if (!s_copy)
		return (0);
	ft_strlcpy(s_copy, s1, len);
	return (s_copy);
}
