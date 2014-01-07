/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/18 17:33:32 by afaucher          #+#    #+#             */
/*   Updated: 2014/01/07 19:19:10 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** This function creates a new point
*/
t_point				*point_new(double x, double y, double z)
{
	t_point			*point;

	point = (t_point*)malloc(sizeof(t_point));
	if (!point)
		return (NULL);
	point->x = x;
	point->y = y;
	point->z = z;
	return (point);
}

/*
** This function places a pixel into an image.
*/
int					pixel_to_img(t_mlx_img *img, int x, int y, int color)
{
	long			index;
	int				i;
	long			max;

	i = 0;
	index = x * (img->bpp / 8) + y * (img->size);
	max = img->width * (img->bpp / 8) + img->height * (img->size);
	while ((i < img->bpp / 8) && index < max && index > 0)
	{
		img->data[index + i] = ((char*)&color)[i];
		i++;
	}
	return (0);
}

int					get_pixel_at(t_mlx_img *img, int x, int y)
{
	long			index;
	int				i;
	long			max;
	int				color;

	i = 0;
	index = x * (img->bpp / 8) + y * (img->size);
	max = img->width * (img->bpp / 8) + img->height * (img->size);
	color = 0;
	while ((i < img->bpp / 8) && index < max && index > 0)
	{
		((char*)&color)[i] = img->data[index + i];
		i++;
	}
	return (color);
}

/*
** Calculates the distance between two points.
*/
float				point_distance(t_point *p1, t_point *p2, double rad)
{
	return (ft_abs(ft_abs(p1->x - p2->x) / ft_cos(rad)));
}

/*
** Moves the point towards a direction
*/
void				move_to(t_wall ***level, t_point *point,
							double rad, double dist)
{
	float			x;
	float			y;

	x = point->x;
	y = point->y;
	x += ft_cos(rad) * dist;
	y -= ft_sin(rad) * dist;
	if (!outofbounds(level, (int)(y / SQR), (int)(x / SQR))
		&& level[(int)(y / SQR)][(int)(x / SQR)]->type)
			return ;
	point->x = x;
	point->y = y;
}
