/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/17 13:11:43 by afaucher          #+#    #+#             */
/*   Updated: 2014/01/08 16:13:42 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** This functions creates an image. It's pretty straightforward actually.
*/
t_mlx_img		*create_img(void *mlx_ptr, void *win_ptr, int width, int height)
{
	t_mlx_img	*mlx_img;
	int			bpp;
	int			size;
	int			endian;

	mlx_img = (t_mlx_img*)malloc(sizeof(t_mlx_img));
	if (!mlx_img)
		return (NULL);
	mlx_img->mlx_ptr = mlx_ptr;
	mlx_img->win_ptr = win_ptr;
	mlx_img->img_ptr = mlx_new_image(mlx_ptr, width, height);
	mlx_img->height = height;
	mlx_img->width = width;
	mlx_img->data = mlx_get_data_addr(mlx_img->img_ptr, &bpp, &size, &endian);
	mlx_img->bpp = bpp;
	mlx_img->size = size;
	mlx_img->endian = endian;
	return (mlx_img);
}

t_mlx_img		*get_xpm_image(void *mlx_ptr, char *filename)
{
	t_mlx_img	*mlx_img;

	mlx_img = (t_mlx_img*)malloc(sizeof(t_mlx_img));
	if (!mlx_img)
		return (NULL);
	mlx_img->mlx_ptr = mlx_ptr;
	mlx_img->win_ptr = NULL;
	mlx_img->img_ptr = mlx_xpm_file_to_image(mlx_ptr, filename,
						&mlx_img->width, &mlx_img->height);
	mlx_img->data = mlx_get_data_addr(mlx_img->img_ptr, &mlx_img->bpp,
										&mlx_img->size, &mlx_img->endian);
	return (mlx_img);
}

int				darken_color(int color, int bpp, char ratio)
{
	int			i;
	int			hex;

	i = 0;
	while (i < bpp / 8)
	{
		hex = ((char*)&color)[i];
		hex = (hex > 0) ? hex : 0xFF + hex;
		hex = hex - ratio;
		if (hex < 0)
			hex = 0;
		((char*)&color)[i] = hex;
		i++;
	}
	return (color);
}

void			img_redraw(t_mlx_img *img)
{
	mlx_destroy_image(img->mlx_ptr, img->img_ptr);
	mlx_new_image(img->mlx_ptr, img->width, img->height);
	mlx_get_data_addr(img->img_ptr, &(img->bpp)
						, &(img->size), &(img->endian));
	draw_image(img);
	mlx_put_image_to_window(img->mlx_ptr, img->win_ptr
								, img->img_ptr, 0, 0);
}
