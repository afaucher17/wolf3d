/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/03 15:56:49 by afaucher          #+#    #+#             */
/*   Updated: 2014/01/03 20:21:38 by afaucher         ###   ########.fr       */
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

# define SQUARE 64
# define SIZE_X 2280
# define SIZE_Y 1280

typedef struct	s_point
{
	long		x;
	long		y;
	long		z;
}				t_point;
typedef struct	s_wall
{
	t_point		*position;
	char		type;
}				t_wall;
typedef struct	s_player
{
	t_point		*position;
	int			angle;
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
	double		zoom;
	int			xgap;
	int			ygap;
	int			bpp;
	int			height;
	int			width;
	int			size;
	int			endian;
}				t_mlx_img;
t_mlx_img		*create_img(void *mlx_ptr, void *img_ptr
							, int height, int width);
t_point			*point_new(long x, long y, long z);
t_wall			*wall_new(int x, int y, int z, char type);
t_game			*game_new(t_wall ***level, t_player *player);
t_player		*player_new(int x, int y, int z, int angle);
t_player		*place_player(t_wall ***level);
int				draw_line(t_mlx_img *img, t_point *pt1, t_point *pt2);
t_wall			***init_tab(t_list *list, int *max);
t_list			*init_list(char *argv, int fd, int *max);
void			img_redraw(t_mlx_img *img);
void			draw_image(t_mlx_img *img);
#endif /* WOLF3D_H */
