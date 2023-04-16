/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sreerink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 18:49:26 by sreerink      #+#    #+#                 */
/*   Updated: 2022/11/28 22:37:34 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

char	*ft_strchr(const char *s, int c)
{
	char			ch;
	char			*str;
	size_t			i;

	ch = (unsigned char) c;
	str = (char *) s;
	i = 0;
	while (ch == '\0')
	{
		if (str[i] == ch)
			return (str + i);
		i++;
	}
	while (str[i] != '\0')
	{
		if (str[i] == ch)
			return (str + i);
		i++;
	}
	return (0);
}
