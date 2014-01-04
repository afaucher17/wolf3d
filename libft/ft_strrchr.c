/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strrchr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 16:20:38 by afaucher          #+#    #+#             */
/*   Updated: 2013/12/01 16:25:15 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	c = (char)c;
	if (*s == '\0' && c != '\0')
		return (NULL);
	while (*s)
		s++;
	if (*s == c)
		return ((char *)s);
	s--;
	while (*s)
	{
		if (*s == c)
		return ((char *)s);
		s--;
	}
	return (NULL);
}
