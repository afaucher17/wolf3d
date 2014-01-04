/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/03 19:01:59 by afaucher          #+#    #+#             */
/*   Updated: 2014/01/03 19:14:52 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_player		*player_new(int x, int y, int z, int angle)
{
	t_player	*new;

	new = (t_player*)malloc(sizeof(t_player));
	if (!new)
		return (NULL);
	new->position = point_new(x, y, z);
	new->angle = angle;
	return (new);
}
