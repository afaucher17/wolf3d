/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/18 17:33:32 by afaucher          #+#    #+#             */
/*   Updated: 2014/01/19 18:54:25 by afaucher         ###   ########.fr       */
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

/*
** Gets the pixel color of an image at a position
*/
size_t				get_pixel_at(t_mlx_img *img, int x, int y)
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
	double			dist;

	if ((rad > PI / 4 && rad < 3 * PI / 4)
		|| (rad > 5 * PI / 4 && rad < 7 * PI / 4))
		dist = ft_abs(ft_abs(p1->y - p2->y) / sin(rad));
	else
		dist = ft_abs(ft_abs(p1->x - p2->x) / cos(rad));
	free(p2);
	return (dist);
}

/*
** Moves the point towards a direction
*/
void				move_to(t_wall ***level, t_point *point,
							double rad, double dist)
{
	double			x;
	double			y;

	x = point->x;
	y = point->y;
	x += cos(rad) * dist;
	y -= sin(rad) * dist;
	if (!outofbounds(level, (int)(y / SQR), (int)(point->x / SQR))
		&& level[(int)(y / SQR)][(int)(point->x / SQR)]->type == 0)
		point->y = y;
	if (!outofbounds(level, (int)(point->y / SQR), (int)(x / SQR))
		&& level[(int)(point->y / SQR)][(int)(x / SQR)]->type == 0)
		point->x = x;
}
