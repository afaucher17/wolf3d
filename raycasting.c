/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/03 20:31:02 by afaucher          #+#    #+#             */
/*   Updated: 2014/01/06 14:53:21 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

/*
** Calculates the distance between two points.
*/
float		point_distance(t_point *p1, t_point *p2, float rad)
{
	return (ft_abs(ft_abs(p1->x - p2->x) / ft_cos(rad)));
}

/*
** Makes an horizontal calculation of the distance between the player and a wall
*/
float		horizontal_raycast(t_game *game, float rad, t_player *player)
{
	t_point	*inter;
	float	px;
	float	py;
	float	xa;
	float	ya;

	inter = point_new(0, 0, 0);
	px = player->position->x;
	py = player->position->y;
	inter->y = (rad < PI) ? (int)(py / SQUARE) * SQUARE - 1
							: (int)(py / SQUARE) * SQUARE + SQUARE;
	inter->x = px + ((py - inter->y) / ft_tan(rad));
	xa = (rad > PI / 2 && rad < 3 * PI / 2) ? -ft_abs(SQUARE / ft_tan(rad)) : ft_abs(SQUARE / ft_tan(rad));
	ya = (rad < PI) ? -SQUARE : SQUARE;
	if (outofbounds(game->level, inter))
		return (-1);
	while (game->level[(int)(inter->y / SQUARE)]
			[(int)(inter->x / SQUARE)]->type == 0)
	{
		inter->x += xa;
		inter->y += ya;
		if (outofbounds(game->level, inter))
			return (-1);
	}
	return (point_distance(player->position, inter, rad));
}

/*
** Makes a vertical calculation of the distance between the player and a wall
*/
float		vertical_raycast(t_game *game, float rad, t_player *player)
{
	t_point	*inter;
	float	px;
	float	py;
	float	xa;
	float	ya;

	inter = point_new(0, 0, 0);
	px = player->position->x;
	py = player->position->y;
	inter->x = (rad < PI / 2 || rad > (3 * PI / 2)) ?
		(int)(px / SQUARE) * SQUARE + SQUARE
		: (int)(px / SQUARE) * SQUARE - 1;
	inter->y = py + ((px - inter->x) * ft_tan(rad));
	xa = (rad < (PI / 2) || rad > (3 * PI / 2)) ? SQUARE : -SQUARE;
	ya = (rad > 0) ? ft_abs(SQUARE * ft_tan(rad)) : -ft_abs(SQUARE * ft_tan(rad));
	if (outofbounds(game->level, inter))
		return (-1);
	while (game->level[(int)(inter->y / SQUARE)]
			[(int)(inter->x / SQUARE)]->type == 0)
	{
		inter->x += xa;
		inter->y += ya;
		if (outofbounds(game->level, inter))
			return (-1);
	}
	return (point_distance(player->position, inter, rad));
}

/*
** Calculates the shortest distance between a player
** and a wall in the chosen direction
*/
float		raycast(t_game *game, float rad, float fov, t_player *player)
{
	float	ver;
	float	hor;
	float	shortest;

	hor = -1;
	ver = -1;
	if (rad != 0 && rad != PI && rad != 2 * PI)
		hor = horizontal_raycast(game, rad, player);
	if (rad != PI / 2 && rad != 3 * PI / 2)
		ver = vertical_raycast(game, rad, player);
	if (hor == -1)
		return (ft_abs(ver * ft_cos(fov)));
	if (ver == -1)
		return (ft_abs(hor * ft_cos(fov)));
	shortest = (hor > ver) ? ver : hor;
	return (ft_abs(shortest * ft_cos(fov)));
}

void		draw_walls(t_game *game, t_player *player, t_mlx_img *img)
{
	float	fov;
	float	inc;
	int		height;
	int		y;
	int		x;

	x = 0;
	fov = -RAD(FOV / 2);
	inc = RAD(FOV / SIZE_X);
	while (x < SIZE_X)
	{
		height = 2 * (player->zoom * SQUARE) / raycast(game,
				ft_getrad(player->rad + fov), ft_getrad(fov), player);
		y = 0;
		while (y < SIZE_Y)
		{
			if ((y > (SIZE_Y / 2 - height / 2))
					&& (y < SIZE_Y / 2 + height / 2))
				pixel_to_img(img, x, y, 0);
			y++;
		}
		fov += inc;
		x++;
	}
}
