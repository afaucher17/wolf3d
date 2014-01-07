/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/18 17:33:32 by afaucher          #+#    #+#             */
/*   Updated: 2014/01/07 08:39:41 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** This function creates a new point
*/
t_point				*point_new(float x, float y, float z)
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
** Calculates the distance between two points.
*/
float				point_distance(t_point *p1, t_point *p2, float rad)
{
	return (ft_abs(ft_abs(p1->x - p2->x) / ft_cos(rad)));
}

/*
** Moves the point towards a direction
*/
void		move_to(t_point *point, float rad, float dist)
{
	point->x += ft_cos(rad) * dist;
	point->y -= ft_sin(rad) * dist;
}
