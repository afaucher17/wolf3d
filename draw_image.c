/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/09 13:04:59 by afaucher          #+#    #+#             */
/*   Updated: 2014/01/19 19:15:31 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** Color the map according to the walls.
*/
static void				color_map(t_mlx_img *img, t_wall_params *wp, double fov)
{
	static t_mlx_img	*wall = NULL;
	static t_mlx_img	*floor = NULL;
	double				resize;
	int					offset;

	offset = (wp->side == 0) ? wp->voffset : wp->hoffset;
	if (!wall)
		wall = get_xpm_image(img->mlx_ptr, "tiles/taric.xpm");
	if (!floor)
		floor = get_xpm_image(img->mlx_ptr, "tiles/pink.xpm");
	resize = wp->height / wall->height;
	if ((wp->y >= (SIZE_Y / 2 - wp->height / 2))
		&& (wp->y <= SIZE_Y / 2 + wp->height / 2))
		pixel_to_img(img, wp->x, wp->y,
					darken_color(get_pixel_at(wall, offset, (int)((wp->y
					- (SIZE_Y / 2 - wp->height / 2)) / resize))
					, wall->bpp, wp->ratio));
	else if (wp->y > SIZE_Y / 2)
		pixel_to_img(img, wp->x, wp->y, floor_raycast(img->game->player, wp
					, fov, floor));
	else if (wp->y < SIZE_Y / 2)
		pixel_to_img(img, wp->x, wp->y, ceiling_raycast(img->game->player, wp
					, fov, floor));
}

/*
** Draw the walls.
*/
void					draw_walls(t_game *game, t_player *player
									, t_mlx_img *img)
{
	double				fov;
	t_wall_params		*wp;

	wp = (t_wall_params*)malloc(sizeof(t_wall_params));
	if (!wp)
		return ;
	wp->x = 0;
	wp->hoffset = -1;
	wp->voffset = -1;
	fov = -RAD(FOV / 2);
	while (wp->x < SIZE_X)
	{
		wp->dist = raycast(game, ft_getrad(fov), wp, player);
		wp->height = (player->zoom * SQR) / wp->dist;
		wp->y = 0;
		while (wp->y < SIZE_Y)
		{
			color_map(img, wp, fov);
			wp->y++;
		}
		fov += RAD(FOV / SIZE_X);
		wp->x++;
	}
	free(wp);
}

void					draw_minimap(t_mlx_img *img)
{
	int					x;
	int					y;

	y = 0;
	while (img->game->level[y])
	{
		x = 0;
		while (img->game->level[y][x])
		{
			if (img->game->level[y][x]->type == 1)
				pixel_to_img(img, (int)((9 * SIZE_X / 10) + x)
							, (int)((SIZE_Y / 8) + y), 0xFFFFFF);
			if ((img->game->player->position->x / SQR) == x
				&& (img->game->player->position->y / SQR) == y)
				pixel_to_img(img, (int)((9 * SIZE_X / 10) + x)
							, (int)((SIZE_Y / 8) + y), 0x000000);
			x++;
		}
		y++;
	}
}

/*
** Draws the image
*/
void					draw_image(t_env *env)
{
	t_mlx_img			*img;

	img = env->img;
	if (!img || !img->game || !img->game->player)
		return ;
	draw_walls(img->game, img->game->player, img);
	if (env->key_m == 1)
		draw_minimap(img);
}
