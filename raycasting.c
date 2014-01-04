/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/03 20:31:02 by afaucher          #+#    #+#             */
/*   Updated: 2014/01/04 19:53:30 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_point		*horizontal_raycast(t_game *game, int angle, int player)
{
	t_point	*inter;
	int		px;
	int		py;
	int		xa;
	int		ya;

	inter = point_new(0, 0, 0);
	px = player->position->x;
	py = player->position->y;
	inter->y = (angle > 0) ? (py / SQUARE) * SQUARE - 1
							: (py / SQUARE) * SQUARE + SQUARE;
	inter->x = px + (py - inter->y) / ft_tan(angle);
	xa = px + ft_tan(angle);
	ya = (angle > 0) ? -SQUARE : SQUARE;
	while (!game->level[inter->x / SQUARE][inter->y / SQUARE]->type)
	{
		inter->x += xa;
		inter->y += ya;
	}
	return (inter);
}

t_point		*vertical_raycast(t_game *game, int angle, int player)
{
	t_point	*inter;
	int		px;
	int		py;
	int		xa;
	int		ya;

	inter = point_new(0, 0, 0);
	px = player->position->x;
	py = player->position->y;
	inter->x = (ft_abs(angle) < 90) ? (px / SQUARE) * SQUARE + SQUARE
									: (px / SQUARE) * SQUARE - 1;
	inter->y = py + (px - inter->x) / ft_tan(angle);
	xa = (ft_abs(angle) < 90) ? SQUARE : -SQUARE;
	ya = py + ft_tan(angle);
	while (!game->level[inter->x / SQUARE][inter->y / SQUARE]->type)
	{
		inter->x += xa;
		inter->y += ya;
	}
	return (inter);
}
