/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/03 20:31:02 by afaucher          #+#    #+#             */
/*   Updated: 2014/01/06 18:56:50 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** Makes an horizontal calculation of the distance between the player and a wall
*/
float				horizontal_raycast(t_game *game, float rad,
										t_player *player)
{
	t_point			*inter;
	float			px;
	float			py;
	float			xa;
	float			ya;

	inter = point_new(0, 0, 0);
	px = player->position->x;
	py = player->position->y;
	inter->y = (rad < PI) ? (int)(py / SQR) * SQR - 1
							: (int)(py / SQR) * SQR + SQR;
	inter->x = px + ((py - inter->y) / ft_tan(rad));
	xa = (rad > PI / 2 && rad < 3 * PI / 2)
		? -ft_abs(SQR / ft_tan(rad)) : ft_abs(SQR / ft_tan(rad));
	ya = (rad < PI) ? -SQR : SQR;
	if (outofbounds(game->level, inter))
		return (-1);
	while (!game->level[(int)(inter->y / SQR)][(int)(inter->x / SQR)]->type)
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
float				vertical_raycast(t_game *game, float rad, t_player *player)
{
	t_point			*inter;
	float			px;
	float			py;
	float			xa;
	float			ya;

	inter = point_new(0, 0, 0);
	px = player->position->x;
	py = player->position->y;
	inter->x = (rad < PI / 2 || rad > (3 * PI / 2)) ?
		(int)(px / SQR) * SQR + SQR
		: (int)(px / SQR) * SQR - 1;
	inter->y = py + ((px - inter->x) * ft_tan(rad));
	xa = (rad < (PI / 2) || rad > (3 * PI / 2)) ? SQR : -SQR;
	ya = (rad < PI) ? -ft_abs(SQR * ft_tan(rad)) : ft_abs(SQR * ft_tan(rad));
	if (outofbounds(game->level, inter))
		return (-1);
	while (!game->level[(int)(inter->y / SQR)][(int)(inter->x / SQR)]->type)
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
float				raycast(t_game *game, float fov, t_wall_params *wp,
							t_player *player)
{
	float			ver;
	float			hor;
	float			rad;

	rad = ft_getrad(player->rad - fov);
	hor = -1;
	ver = -1;
	if (rad != 0 && rad != PI && rad != 2 * PI)
		hor = horizontal_raycast(game, rad, player);
	if (rad != PI / 2 && rad != 3 * PI / 2)
		ver = vertical_raycast(game, rad, player);
	if ((hor == -1 || ver < hor) && ver != -1)
	{
		wp->color = (rad < PI / 2 || rad > 3 * PI / 2) ? 0x636363 : 0x1f1f1f;
		return (ft_abs(ver * ft_cos(fov)));
	}
	else if ((ver == -1 || ver > hor) && hor != -1)
	{
		wp->color = (rad < PI) ? 0xCCCCCC : 0x333333;
		return (ft_abs(hor * ft_cos(fov)));
	}
	return (0.0);
}

void				color_map(t_mlx_img *img, t_wall_params *wp)
{
	if ((wp->y > (SIZE_Y / 2 - wp->height / 2))
		&& (wp->y < SIZE_Y / 2 + wp->height / 2))
		pixel_to_img(img, wp->x, wp->y, wp->color);
	else if (wp->y < SIZE_Y / 2)
		pixel_to_img(img, wp->x, wp->y, 0x99CCFF);
	else if (wp->y > SIZE_Y / 2)
		pixel_to_img(img, wp->x, wp->y, 0x4A7400);
}


void				draw_walls(t_game *game, t_player *player, t_mlx_img *img)
{
	float			fov;
	float			inc;
	t_wall_params	*wp;

	wp = (t_wall_params*)malloc(sizeof(t_wall_params));
	if (!wp)
		return ;
	wp->x = 0;
	fov = -RAD(FOV / 2);
	inc = RAD(FOV / SIZE_X);
	while (wp->x < SIZE_X)
	{
		wp->height = 2 * (player->zoom * SQR) / raycast(game,
				ft_getrad(fov), wp, player);
		wp->y = 0;
		while (wp->y < SIZE_Y)
		{
			color_map(img, wp);
			wp->y++;
		}
		fov += inc;
		wp->x++;
	}
}
