/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_tolower.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sreerink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 18:04:30 by sreerink      #+#    #+#                 */
/*   Updated: 2022/11/28 22:35:50 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		c += 32;
	return (c);
}