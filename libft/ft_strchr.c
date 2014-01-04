/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 16:17:00 by afaucher          #+#    #+#             */
/*   Updated: 2013/12/01 14:38:18 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	c = (char)c;
	while (*s)
	{
		if (c == *s)
			return ((char *) s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}
