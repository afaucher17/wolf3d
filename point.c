/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/18 17:33:32 by afaucher          #+#    #+#             */
/*   Updated: 2014/01/04 18:11:55 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_point		*point_new(long x, long y, long z)
{
	t_point	*point;

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
int					pixel_to_img(t_mlx_img *img, long x, long y, long z)
{
	long			index;
	int				i;
	size_t			color;
	size_t			colorval;
	long			max;

	i = 0;
	index = x * (img->bpp / 8) + y * (img->size);
	max = img->width * (img->bpp / 8) + img->height * (img->size);
	color = 0;
	colorval = mlx_get_color_value(img->mlx_ptr, color);
	if (z > 0)
		((char*)&colorval)[2] = (z > 255) ? 255 : z;
	((char*)&colorval)[1] = (z > 0) ? 0x88 : 0x33;
	if (z <= 0)
		((char*)&colorval)[0] = (z < -255) ? 0 : 255 + z;
	colorval = (z > 400) ? 0xFFFFFF : colorval;
	colorval = (z < -255) ? 0x0000CC : colorval;
	while ((i < img->bpp / 8) && index < max && index > 0)
	{
		img->data[index + i] = ((char*)&colorval)[i];
		i++;
	}
	return (0);
}

/*
** Second method of drawing a line
*/
static int		draw_line_two(t_mlx_img *img, t_point *pt1, t_point *pt2)
{
	long		y;
	long		x1;
	long		x2;
	long		y1;
	long		y2;

	x1 = pt1->x;
	x2 = pt2->x;
	y1 = pt1->y;
	y2 = pt2->y;
	y = y1;
	while (y < y2 && y < img->height)
	{
		if (y > 0 && x1 + (((x2 - x1) * (y - y1)) / (y2 - y1)) > 0
				&& x1 + (((x2 - x1) * (y - y1)) / (y2 - y1)) < img->width)
		pixel_to_img(img
				, x1 + (((x2 - x1) * (y - y1))
					/ (y2 - y1)), y, ((pt1->z + pt2->z) / 2));
		y++;
	}
	return (1);
}

/*
** First method of drawing a line
*/
static int			draw_line_one(t_mlx_img *img, t_point *pt1, t_point *pt2)
{
	long		x;
	long		x1;
	long		x2;
	long		y1;
	long		y2;

	x1 = pt1->x;
	x2 = pt2->x;
	y1 = pt1->y;
	y2 = pt2->y;
	x = x1;
	while (x < x2 && x < img->width)
	{
		if (x > 0 && y1 + (((y2 - y1) * (x - x1)) / (x2 - x1)) > 0
				&& y1 + (((y2 - y1) * (x - x1)) / (x2 - x1)) < img->height)
		pixel_to_img(img, x, y1
						+ (((y2 - y1) * (x - x1))
							/ (x2 - x1)), (pt1->z + pt2->z) / 2);
		x++;
	}
	return (1);
}

/*
** Draws a line between two points
*/
int					draw_line(t_mlx_img *img, t_point *pt1, t_point *pt2)
{
	long			x1;
	long			x2;
	long			y1;
	long			y2;
	long			abs;

	x1 = pt1->x;
	x2 = pt2->x;
	y1 = pt1->y;
	y2 = pt2->y;
	abs = ((y2 - y1) >= 0) ? (y2 - y1) : -(y2 - y1);
	if (x1 <= x2 && (x2 - x1) >= abs)
		return (draw_line_one(img, pt1, pt2));
	else if (x1 > x2 && (x1 - x2) >= abs)
		return (draw_line_one(img, pt2, pt1));
	else if (y1 <= y2)
		return (draw_line_two(img, pt1, pt2));
	else if (y1 > y2)
		return (draw_line_two(img, pt2, pt1));
	return (0);
}
