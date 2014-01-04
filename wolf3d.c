/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/03 15:54:06 by afaucher          #+#    #+#             */
/*   Updated: 2014/01/03 20:30:47 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			draw_image(t_mlx_img *img)
{
	t_wall		***tab;
	int			x;
	int			y;

	tab = img->game->level;
	x = 0;
	while (tab[x])
	{
		y = 0;
		while (tab[x][y])
		{
			ft_putnbr(tab[x][y]->type);
			y++;
		}
		ft_putendl("");
		x++;
	}
	ft_putstr("Player : ");
	ft_putnbr(img->game->player->position->x);
	ft_putstr(";");
	ft_putnbr(img->game->player->position->y);
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
	img->zoom += (keycode == KEY_Z && img->zoom < 200) ? 5 : 0;
	img->zoom -= (keycode == KEY_X && img->zoom > 5) ? 5 : 0;
	img->ygap -= (keycode == KEY_UP && img->ygap > -(img->height)) ? 100 : 0;
	img->ygap += (keycode == KEY_DOWN && img->ygap < img->height * 2) ? 100 : 0;
	img->xgap += (keycode == KEY_RIGHT && img->xgap < img->width * 2) ? 100 : 0;
	img->xgap -= (keycode == KEY_LEFT && img->xgap > -(img->width)) ? 100 : 0;
	if (keycode == KEY_UP || keycode == KEY_DOWN || keycode == KEY_RIGHT
			|| keycode == KEY_LEFT || keycode == KEY_Z || keycode == KEY_X)
		img_redraw(img);
	return (0);
}

void			fdf(char *str, int fd)
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
		ft_putendl_fd("usage: ./fdf file1", 2);
	else
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			perror(ft_strjoin("fdf: ", argv[1]));
			return (1);
		}
		fdf(argv[1], fd);
	}
	return (0);
}
