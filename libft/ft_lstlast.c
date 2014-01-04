/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/26 13:36:02 by afaucher          #+#    #+#             */
/*   Updated: 2013/11/27 16:48:13 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*cur;

	if (lst)
	{
		cur = lst;
		while (cur->next)
			cur = cur->next;
		return (cur);
	}
	return (NULL);
}
