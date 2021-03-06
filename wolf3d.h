/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/03 15:56:49 by afaucher          #+#    #+#             */
/*   Updated: 2014/01/19 19:12:06 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <mlx.h>
# include <stdio.h>
# include <math.h>

# define KEY_Z 122
# define KEY_X 120
# define KEY_LEFT 65361
# define KEY_UP 65362
# define KEY_RIGHT 65363
# define KEY_DOWN 65364
# define KEY_ESC 65307
# define KEY_M 109

# define FOV 60.0
# define SQR 256
# define SIZE_X 640.0
# define SIZE_Y 400.0

typedef struct	s_point
{
	double		x;
	double		y;
	double		z;
}				t_point;

typedef struct	s_wall
{
	t_point		*position;
	char		type;
}				t_wall;

typedef struct	s_player
{
	t_point		*position;
	double		rad;
	double		zoom;
}				t_player;

typedef struct	s_game
{
	t_wall		***level;
	t_player	*player;
}				t_game;

typedef struct	s_mlx_img
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*data;
	t_game		*game;
	int			bpp;
	int			height;
	int			width;
	int			size;
	int			endian;
}				t_mlx_img;

typedef struct	s_env
{
	t_mlx_img	*img;
	char		key_esc;
	char		key_right;
	char		key_left;
	char		key_up;
	char		key_down;
	char		key_m;
}				t_env;

typedef struct	s_wall_params
{
	int			x;
	int			y;
	double		height;
	double		hor;
	double		ver;
	double		dist;
	int			side;
	int			hoffset;
	int			voffset;
	char		ratio;
}				t_wall_params;

/*
** wolf3d.c
*/
void			wolf3d(char *str, int fd);

/*
** image.c
*/
t_mlx_img		*create_img(void *mlx_ptr, void *img_ptr
							, int height, int width);
t_mlx_img		*get_xpm_image(void *mlx_ptr, char *filename);
int				darken_color(int color, int bpp, char ratio);
void			img_redraw(t_env *env);

/*
** point.c
*/
t_point			*point_new(double x, double y, double z);
int				pixel_to_img(t_mlx_img *img, int x, int y, int color);
size_t			get_pixel_at(t_mlx_img *img, int x, int y);
float			point_distance(t_point *p1, t_point *p2, double rad);
void			move_to(t_wall ***level, t_point *point,
						double rad, double dist);

/*
** wall.c
*/
t_wall			*wall_new(int x, int y, int z, char type);

/*
** game.c
*/
t_game			*game_new(t_wall ***level, t_player *player);
t_player		*place_player(t_wall ***level);
char			outofbounds(t_wall ***level, double y, double x);

/*
** player.c
*/
t_player		*player_new(double x, double y, double z, double rad);

/*
** draw_image.c
*/
void			draw_walls(t_game *game, t_player *player, t_mlx_img *img);
void			draw_image(t_env *env);

/*
** tab.c
*/
t_wall			***init_tab(t_list *list, int *max);
int				get_tabwidth(t_wall ***tab);
int				get_tabheight(t_wall ***tab);
t_list			*init_list(char *argv, int fd, int *max);

/*
** raycasting.c
*/
double			raycast(t_game *game, double fov,
						t_wall_params *wp, t_player *player);
size_t			floor_raycast(t_player *player, t_wall_params *wp,
								double fov, t_mlx_img *floor);
size_t			ceiling_raycast(t_player *player, t_wall_params *wp,
								double fov, t_mlx_img *floor);
#endif /* !WOLF3D_H */
