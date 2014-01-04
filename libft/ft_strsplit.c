/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 16:46:42 by afaucher          #+#    #+#             */
/*   Updated: 2013/12/18 18:52:25 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char		**alloc_tab(char const *s, char c)
{
	size_t		size;

	size = 1;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		size++;
		while (*s && *s != c)
			s++;
	}
	return ((char **)malloc(sizeof(char *) * (size)));
}

char			**ft_strsplit(char const *s, char c)
{
	char		**tab;
	const char	*save;
	char		**tab_save;
	size_t		len;

	tab = alloc_tab(s, c);
	if (!tab)
		return (NULL);
	tab_save = tab;
	while (*s)
	{
		len = 0;
		while (*s && *s == c)
			s++;
		save = s;
		while (*s && *s != c)
		{
			s++;
			len++;
		}
		*tab = ft_strsub(save, 0, len);
		tab++;
	}
	*tab = NULL;
	return (tab_save);
}
