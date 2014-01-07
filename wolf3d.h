/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/03 15:56:49 by afaucher          #+#    #+#             */
/*   Updated: 2014/01/07 09:32:01 by afaucher         ###   ########.fr       */
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
# define KEY_Z 122
# define KEY_X 120
# define KEY_LEFT 65361
# define KEY_UP 65362
# define KEY_RIGHT 65363
# define KEY_DOWN 65364
# define KEY_ESC 65307

# define FOV 60
# define SQR 256
# define SIZE_X 1280
# define SIZE_Y 800

typedef struct	s_point
{
	float		x;
	float		y;
	float		z;
}				t_point;
typedef struct	s_wall
{
	t_point		*position;
	char		type;
}				t_wall;
typedef struct	s_player
{
	t_point		*position;
	float		rad;
	float		zoom;
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
typedef struct	s_wall_params
{
	int			x;
	int			y;
	float		height;
	int			color;
}				t_wall_params;
t_mlx_img		*create_img(void *mlx_ptr, void *img_ptr
							, int height, int width);
t_point			*point_new(float x, float y, float z);
t_wall			*wall_new(int x, int y, int z, char type);
t_game			*game_new(t_wall ***level, t_player *player);
t_player		*player_new(float x, float y, float z, float rad);
t_player		*place_player(t_wall ***level);
void			move_to(t_point *point, float rad, float dist);
int				pixel_to_img(t_mlx_img *img, int x, int y, int color);
float			point_distance(t_point *p1, t_point *p2, float rad);
char			outofbounds(t_wall ***level, float y, float x);
int				draw_line(t_mlx_img *img, t_point *pt1, t_point *pt2);
t_wall			***init_tab(t_list *list, int *max);
int				get_tabwidth(t_wall ***tab);
int				get_tabheight(t_wall ***tab);
t_list			*init_list(char *argv, int fd, int *max);
void			draw_walls(t_game *game, t_player *player, t_mlx_img *img);
void			img_redraw(t_mlx_img *img);
void			draw_image(t_mlx_img *img);
#endif /* WOLF3D_H */
