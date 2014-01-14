/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/18 17:41:06 by afaucher          #+#    #+#             */
/*   Updated: 2014/01/13 19:00:59 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_list			*init_list(char *argv, int fd, int *max)
{
	t_list		*list;
	char		**tab;
	char		*buf;
	int			i;
	int			res;

	list = NULL;
	buf = NULL;
	while ((res = ft_get_next_line(fd, &buf)) > 0)
	{
		i = 0;
		tab = ft_strsplit(buf, ' ');
		free(buf);
		while (tab[i])
			i++;
		*max = (i > *max) ? i : *max;
		if (i > 0)
			ft_lstaddlast(&list, ft_lstnew(tab, (sizeof(char *) * (i + 1))));
	}
	if (res == -1)
	{
		perror(ft_strjoin("wolf3d: ", argv));
		exit(1);
	}
	return (list);
}

static t_wall	***init_emptytab(int lines, int columns)
{
	t_wall		***tab;
	int			x;
	int			y;

	tab = (t_wall***)malloc(sizeof(t_wall**) * (lines + 3));
	x = 0;
	while (x < (lines + 2))
	{
		tab[x] = (t_wall**)malloc(sizeof(t_wall*) * (columns + 3));
		y = 0;
		while (y < (columns + 2))
		{
			tab[x][y] = wall_new(y, x, 0, -1);
			y++;
		}
		tab[x][y] = NULL;
		x++;
	}
	tab[x] = NULL;
	return (tab);
}

int				get_tabwidth(t_wall ***wall)
{
	int			i;

	i = 0;
	while (wall[0][i])
		i++;
	return (i);
}

int				get_tabheight(t_wall ***wall)
{
	int			i;

	i = 0;
	while (wall[i])
		i++;
	return (i);
}

t_wall			***init_tab(t_list *list, int *max)
{
	t_wall		***tab;
	char		**strtab;
	int			x;
	int			y;

	tab = init_emptytab(ft_lstlen(list), *max);
	y = 1;
	while (list)
	{
		strtab = list->content;
		x = 1;
		while (*strtab)
		{
			tab[y][x] = wall_new(x, y, 0, (ft_atoi(*strtab++) != 0));
			x++;
		}
		y++;
		list = list->next;
	}
	return (tab);
}
