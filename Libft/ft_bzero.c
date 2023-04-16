/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sreerink <sreerink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/22 16:46:26 by sreerink      #+#    #+#                 */
/*   Updated: 2022/11/26 21:46:56 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str_caster;
	size_t			i;

	str_caster = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		str_caster[i] = 0;
		i++;
	}
}
