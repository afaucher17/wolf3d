/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/03 18:59:09 by afaucher          #+#    #+#             */
/*   Updated: 2014/01/03 19:16:35 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_game		*game_new(t_wall ***level, t_player *player)
{
	t_game	*new;

	new = (t_game*)malloc(sizeof(t_game));
	if (!new)
		return (NULL);
	new->level = level;
	new->player = player;
	return (new);
}
