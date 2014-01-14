/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/03 18:59:09 by afaucher          #+#    #+#             */
/*   Updated: 2014/01/14 07:53:13 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** Creates a new game
*/
t_game		*game_new(t_wall ***level, t_player *player)
{
	t_game	*new;

	new = (t_game*)malloc(sizeof(t_game));
	if (!new)
		return (NULL);
	new->level = level;
	new->player = player;
	return (new);
}

/*
** Places the player into a map
*/
t_player	*place_player(t_wall ***level)
{
	int		x;
	int		y;

	y = 0;
	while (level[y])
	{
		x = 0;
		while (level[y][x])
		{
			if (level[y][x]->type == 0)
				return (player_new(SQR / 2 + (x * SQR),
									SQR / 2 + (y * SQR),
									level[y][x]->position->z, 0));
			x++;
		}
		y++;
	}
	exit(ft_putendl_fd("No empty square in this map", 2));
	return (NULL);
}

/*
** Checks if a point is out of bounds
*/
char		outofbounds(t_wall ***level, double y, double x)
{
	return ((int)x >= get_tabwidth(level) || (int)x < 0
			|| (int)y >= get_tabheight(level) || (int)y < 0);
}
