/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strintab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/27 14:02:59 by afaucher          #+#    #+#             */
/*   Updated: 2013/11/27 15:24:52 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strintab(char *str, char **tab, int size)
{
	while (size > 0)
	{
		if (ft_strequ(str, *tab))
			return (1);
		tab++;
		size--;
	}
	return (0);
}
