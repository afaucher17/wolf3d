/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/09 13:10:11 by afaucher          #+#    #+#             */
/*   Updated: 2014/01/19 17:59:16 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** Makes an horizontal calculation of the distance between the player and a wall
*/
static double			horizontal_raycast(t_game *game, double rad,
										t_player *player, int *offset)
{
	t_point				*ip;
	double				px;
	double				py;
	double				xa;
	double				ya;

	ip = point_new(0, 0, 0);
	px = player->position->x;
	py = player->position->y;
	ip->y = AUP(rad) ? (int)(py / SQR) * SQR - 1 : (int)(py / SQR) * SQR + SQR;
	ip->x = px + ((py - ip->y) / tan(rad));
	xa = ALEFT(rad) ? -ft_abs((SQR / tan(rad))) : ft_abs((SQR / tan(rad)));
	ya = AUP(rad) ? -SQR : SQR;
	if (outofbounds(game->level, ip->y / SQR, (ip->x + ALEFT(rad)) / SQR))
		return (-1);
	while (!game->level[(int)(ip->y / SQR)]
			[(int)((ip->x + ALEFT(rad)) / SQR)]->type)
	{
		ip->x += xa;
		ip->y += ya;
		if (outofbounds(game->level, ip->y / SQR, (ip->x + ALEFT(rad)) / SQR))
			return (-1);
	}
	*offset = (int)(ip->x) % SQR;
	return (point_distance(player->position, ip, rad));
}

/*
** Makes a vertical calculation of the distance between the player and a wall
*/
static double			vertical_raycast(t_game *game, double rad,
									t_player *player, int *offset)
{
	t_point				*ip;
	double				px;
	double				py;
	double				xa;
	double				ya;

	ip = point_new(0, 0, 0);
	px = player->position->x;
	py = player->position->y;
	ip->x = ARIGHT(rad) ? (int)(px / SQR) * SQR + SQR
				: (int)(px / SQR) * SQR - 1;
	ip->y = py + ((px - ip->x) * tan(rad)) + AUP(rad);
	xa = ARIGHT(rad) ? SQR : -SQR;
	ya = AUP(rad) ? -ft_abs(SQR * tan(rad)) : ft_abs(SQR * tan(rad));
	if (outofbounds(game->level, ip->y / SQR, ip->x / SQR))
		return (-1);
	while (!game->level[(int)(ip->y / SQR)][(int)(ip->x / SQR)]->type)
	{
		ip->x += xa;
		ip->y += ya;
		if (outofbounds(game->level, ip->y / SQR, ip->x / SQR))
			return (-1);
	}
	*offset = (int)(ip->y) % SQR;
	return (point_distance(player->position, ip, rad));
}

/*
** Calculates the shortest distance between a player
** and a wall in the chosen direction
*/
double			raycast(t_game *game, double fov, t_wall_params *wp,
							t_player *player)
{
	double				rad;

	rad = ft_getrad(player->rad - fov);
	wp->hor = horizontal_raycast(game, rad, player, &wp->hoffset);
	wp->ver = vertical_raycast(game, rad, player, &wp->voffset);
	if ((wp->hor == -1 || wp->ver < wp->hor) && wp->ver != -1)
	{
		wp->ratio = (rad < PI / 2 || rad > 3 * PI / 2) ? 0x05 : 0x20;
		wp->side = 0;
		return (ft_abs(wp->ver) * cos(fov));
	}
	else
	{
		wp->ratio = (rad < PI) ? -0x25 : 0x70;
		wp->side = 1;
		return (ft_abs(wp->hor * cos(fov)));
	}
}

/*
** Makes the floor raycast
*/
size_t					floor_raycast(t_player	*player, t_wall_params *wp,
										double fov, t_mlx_img *floor)
{
	double				curdist;
	double				weight;
	double				x;
	double				y;

	curdist = SIZE_Y / (2.0 * wp->y - SIZE_Y) * SQR;
	weight = (curdist) / (wp->dist);
	x = (1.0 - weight) * (player->position->x) + weight
		* ((player->position->x) + wp->dist * cos(ft_getrad(fov - player->rad))
		/ cos(-fov));
	y = (1.0 - weight) * (player->position->y) + weight
		* ((player->position->y) + wp->dist * sin(ft_getrad(fov - player->rad))
		/ cos(-fov));
	x = ft_abs(x);
	y = ft_abs(y);
	return (get_pixel_at(floor, (int)x % floor->width, (int)y % floor->height));
}

/*
** Makes the ceiling raycast
*/
size_t					ceiling_raycast(t_player *player, t_wall_params *wp,
										double fov, t_mlx_img *ceiling)
{
	double				curdist;
	double				weight;
	double				x;
	double				y;

	curdist = SIZE_Y / (SIZE_Y - wp->y * 2.0) * SQR;
	weight = (curdist) / (wp->dist);
	x = (1.0 - weight) * (player->position->x) + weight
		* ((player->position->x) + wp->dist * cos(ft_getrad(fov - player->rad))
		/ cos(-fov));
	y = (1.0 - weight) * (player->position->y) + weight
		* ((player->position->y) + wp->dist * sin(ft_getrad(fov - player->rad))
		/ cos(-fov));
	x = ft_abs(x);
	y = ft_abs(y);
	return (get_pixel_at(ceiling, (int)x % ceiling->width
						, (int)y % ceiling->height));

}
