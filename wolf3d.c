/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/03 15:54:06 by afaucher          #+#    #+#             */
/*   Updated: 2014/01/07 15:23:22 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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
	t_player	*player;

	player = img->game->player;
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_RIGHT)
		player->rad -= 0.15;
	if (keycode == KEY_LEFT)
		player->rad += 0.15;
	if (keycode == KEY_UP)
		move_to(img->game->level, player->position, player->rad, 90);
	if (keycode == KEY_DOWN)
		move_to(img->game->level, player->position, player->rad, -90);
	player->rad = ft_getrad(player->rad);
	if (keycode)
		img_redraw(img);
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
	mlx_hook(win_ptr, 2, (1L << 0), key_hook, mlx_img);
	mlx_do_key_autorepeaton(mlx_ptr);
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
