/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/03 20:31:02 by afaucher          #+#    #+#             */
/*   Updated: 2014/01/07 19:32:24 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** Makes an horizontal calculation of the distance between the player and a wall
*/
double				horizontal_raycast(t_game *game, double rad,
										t_player *player, int *offset)
{
	t_point			*ip;
	double			px;
	double			py;
	double			xa;
	double			ya;

	ip = point_new(0, 0, 0);
	px = player->position->x;
	py = player->position->y;
	ip->y = AUP(rad) ? (int)(py / SQR) * SQR - 1 : (int)(py / SQR) * SQR + SQR;
	ip->x = px + ((py - ip->y) / ft_tan(rad));
	xa = ALEFT(rad) ? -ft_abs(SQR / ft_tan(rad)) : ft_abs(SQR / ft_tan(rad));
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
double				vertical_raycast(t_game *game, double rad,
									t_player *player, int *offset)
{
	t_point			*ip;
	double			px;
	double			py;
	double			xa;
	double			ya;

	ip = point_new(0, 0, 0);
	px = player->position->x;
	py = player->position->y;
	ip->x = ARIGHT(rad) ? (int)(px / SQR) * SQR + SQR
				: (int)(px / SQR) * SQR - 1;
	ip->y = py + ((px - ip->x) * ft_tan(rad)) + AUP(rad);
	xa = ARIGHT(rad) ? SQR : -SQR;
	ya = AUP(rad) ? -ft_abs(SQR * ft_tan(rad)) : ft_abs(SQR * ft_tan(rad));
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
double				raycast(t_game *game, double fov, t_wall_params *wp,
							t_player *player)
{
	double			ver;
	double			hor;
	double			rad;

	rad = ft_getrad(player->rad - fov);
	hor = -1;
	ver = -1;
	if (rad != 0 && rad != PI && rad != 2 * PI)
		hor = horizontal_raycast(game, rad, player, &wp->hoffset);
	if (rad != PI / 2 && rad != 3 * PI / 2)
		ver = vertical_raycast(game, rad, player, &wp->voffset);
	if ((hor == -1 || ver < hor) && ver != -1)
	{
		wp->ratio = (rad < PI / 2 || rad > 3 * PI / 2) ? 2 : 4;
		wp->hoffset = -1;
		return (ft_abs(ver * ft_cos(fov)));
	}
	else if ((ver == -1 || ver > hor) && hor != -1)
	{
		wp->ratio = (rad < PI) ? 1 : 3;
		wp->voffset = -1;
		return (ft_abs(hor * ft_cos(fov)));
	}
	return (0.0);
}

void				color_map(t_mlx_img *img, t_wall_params *wp)
{
	static t_mlx_img	*sprite = NULL;
	double				resize;
	int					offset;

	offset = (wp->hoffset == -1) ? wp->voffset : wp->hoffset;
	if (!sprite)
		sprite = get_xpm_image(img->mlx_ptr, "tile1.xpm");
	resize = wp->height / sprite->height;
	if ((wp->y > (SIZE_Y / 2 - wp->height / 2))
		&& (wp->y < SIZE_Y / 2 + wp->height / 2))
		pixel_to_img(img, wp->x, wp->y,
					get_pixel_at(sprite, (int)offset, (int)((wp->y
					- (SIZE_Y / 2 - wp->height / 2)) / resize)));
	else if (wp->y < SIZE_Y / 2)
		pixel_to_img(img, wp->x, wp->y, 0xDA6339);
	else if (wp->y > SIZE_Y / 2)
		pixel_to_img(img, wp->x, wp->y, 0x604904);
}


void				draw_walls(t_game *game, t_player *player, t_mlx_img *img)
{
	double			fov;
	double			inc;
	t_wall_params	*wp;

	wp = (t_wall_params*)malloc(sizeof(t_wall_params));
	if (!wp)
		return ;
	wp->x = 0;
	wp->hoffset = -1;
	wp->voffset = -1;
	fov = -RAD(FOV / 2);
	inc = RAD(FOV / SIZE_X);
	while (wp->x < SIZE_X)
	{
		wp->height = 4 * (player->zoom * SQR) / raycast(game,
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
