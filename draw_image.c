/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/09 13:04:59 by afaucher          #+#    #+#             */
/*   Updated: 2014/01/09 13:18:12 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void				color_map(t_mlx_img *img, t_wall_params *wp)
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
					darken_color(get_pixel_at(sprite, (int)offset, (int)((wp->y
					- (SIZE_Y / 2 - wp->height / 2)) / resize)),
					sprite->bpp, wp->ratio));
	else if (wp->y < SIZE_Y / 2)
		pixel_to_img(img, wp->x, wp->y, 0xDA6339);
	else if (wp->y > SIZE_Y / 2)
		pixel_to_img(img, wp->x, wp->y, 0x604904);
}


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
		wp->height = 4 * (player->zoom * SQR) / raycast(game,
				ft_getrad(fov), wp, player);
		wp->y = 0;
		while (wp->y < SIZE_Y)
		{
			color_map(img, wp);
			wp->y++;
		}
		fov += RAD(FOV / SIZE_X);
		wp->x++;
	}
	free(wp);
}

void					draw_image(t_mlx_img *img)
{
	if (!img || !img->game || !img->game->player)
		return ;
	draw_walls(img->game, img->game->player, img);
}
