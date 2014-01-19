/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/09 12:43:19 by afaucher          #+#    #+#             */
/*   Updated: 2014/01/19 18:00:26 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		expose_hook(t_mlx_img *img)
{
	draw_image(img);
	mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img_ptr, 0, 0);
	return (1);
}

static int		keypress_hook(int keycode, t_env *env)
{
	env->key_esc = (keycode == KEY_ESC) ? 1 : env->key_esc;
	env->key_right = (keycode == KEY_RIGHT) ? 1 : env->key_right;
	env->key_left = (keycode == KEY_LEFT) ? 1 : env->key_left;
	env->key_up = (keycode == KEY_UP) ? 1 : env->key_up;
	env->key_down = (keycode == KEY_DOWN) ? 1 : env->key_down;
	return (0);
}

static int		keyrelease_hook(int keycode, t_env *env)
{
	env->key_esc = (keycode == KEY_ESC) ? 0 : env->key_esc;
	env->key_right = (keycode == KEY_RIGHT) ? 0 : env->key_right;
	env->key_left = (keycode == KEY_LEFT) ? 0 : env->key_left;
	env->key_up = (keycode == KEY_UP) ? 0 : env->key_up;
	env->key_down = (keycode == KEY_DOWN) ? 0 : env->key_down;
	return (0);
}

static int		loop_hook(t_env *env)
{
	t_player	*player;

	player = env->img->game->player;
	if (env->key_esc)
		exit(EXIT_SUCCESS);
	player->rad += (env->key_right) ? -PI / 20 : 0;
	player->rad += (env->key_left) ? PI / 20 : 0;
	if (env->key_up)
		move_to(env->img->game->level, player->position, player->rad, SQR / 10);
	if (env->key_down)
		move_to(env->img->game->level, player->position,
				player->rad, -(SQR / 10));
	player->rad = ft_getrad(player->rad);
	img_redraw(env->img);
	return (0);
}

void			wolf3d(char *str, int fd)
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_wall		***tab;
	t_env		*env;
	int			max;

	env = (t_env*)malloc(sizeof(t_env));
	if (!env)
		return ;
	mlx_ptr = mlx_init();
	tab = init_tab(init_list(str, fd, &max), &max);
	win_ptr = mlx_new_window(mlx_ptr, SIZE_X, SIZE_Y, "WOLF3D");
	env->img = create_img(mlx_ptr, win_ptr, SIZE_X, SIZE_Y);
	env->img->game = game_new(tab, place_player(tab));
	close (fd);
	env->key_esc = 0;
	env->key_right = 0;
	env->key_left = 0;
	env->key_up = 0;
	env->key_down = 0;
	mlx_hook(win_ptr, 2, (1L << 0), keypress_hook, env);
	mlx_key_hook(win_ptr, keyrelease_hook, env);
	mlx_loop_hook(mlx_ptr, loop_hook, env);
	mlx_expose_hook(win_ptr, expose_hook, env->img);
	mlx_loop(mlx_ptr);
}
