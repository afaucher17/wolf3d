/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/03 18:04:14 by afaucher          #+#    #+#             */
/*   Updated: 2014/01/19 18:00:04 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** Creates a new wall
*/
t_wall		*wall_new(int x, int y, int z, char type)
{
	t_wall	*new;

	new = (t_wall*)malloc(sizeof(t_wall));
	if (!new)
		return (NULL);
	new->position = point_new(x, y, z);
	new->type = type;
	return (new);
}
