/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sreerink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 21:15:46 by sreerink      #+#    #+#                 */
/*   Updated: 2022/11/28 22:31:10 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str_caster;
	size_t			i;

	str_caster = (unsigned char *) b;
	i = 0;
	while (i < len)
	{
		str_caster[i] = c;
		i++;
	}
	return (str_caster);
}
