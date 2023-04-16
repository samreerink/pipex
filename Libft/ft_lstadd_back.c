/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sreerink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/28 20:07:28 by sreerink      #+#    #+#                 */
/*   Updated: 2022/11/28 20:07:33 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (new != NULL)
	{
		if (*lst != NULL)
			ft_lstlast(*lst)->next = new;
		else
			*lst = new;
	}
}
