/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/03 15:54:06 by afaucher          #+#    #+#             */
/*   Updated: 2014/01/06 13:42:32 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

void			draw_image(t_mlx_img *img)
{
	if (!img || !img->game || !img->game->player)
		return ;
	draw_walls(img->game, img->game->player, img);
}

int				expose_hook(t_mlx_img *img)
{
	draw_image(img);
	mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img_ptr, 0, 0);
	return (1);
}

int				key_hook(int keycode, t_mlx_img *img)
{
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_RIGHT)
		img->game->player->rad -= 0.05;
	if (keycode == KEY_LEFT)
		img->game->player->rad += 0.05;
	if (keycode == KEY_UP)
		img->game->player->position->x += 30;
	if (keycode == KEY_DOWN)
		img->game->player->position->x -= 30;
	img->game->player->rad = ft_getrad(img->game->player->rad);
	if (keycode)
		img_redraw(img);
	img = NULL;
	return (0);
}

void			wolf3d(char *str, int fd)
{
	void		*mlx_ptr;
	t_mlx_img	*mlx_img;
	void		*win_ptr;
	t_wall		***tab;
	int			max;

	max = 0;
	mlx_ptr = mlx_init();
	tab = init_tab(init_list(str, fd, &max), &max);
	win_ptr = mlx_new_window(mlx_ptr, SIZE_X, SIZE_Y, "WOLF3D");
	mlx_img = create_img(mlx_ptr, win_ptr, SIZE_X, SIZE_Y);
	mlx_img->game = game_new(tab, place_player(tab));
	close (fd);
	mlx_key_hook(win_ptr, key_hook, mlx_img);
	mlx_expose_hook(win_ptr, expose_hook, mlx_img);
	mlx_loop(mlx_ptr);
}

int				main(int argc, char **argv)
{
	int			fd;

	if (argc < 2)
		ft_putendl_fd("usage: ./wolf3d file1", 2);
	else
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			perror(ft_strjoin("wolf3d: ", argv[1]));
			return (1);
		}
		wolf3d(argv[1], fd);
	}
	return (0);
}
