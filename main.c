/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/04 13:27:55 by afaucher          #+#    #+#             */
/*   Updated: 2014/01/04 16:05:09 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "maths.h"
#include <stdio.h>

int		main()
{
	int	i;

	i = -180;
	while (i <= 180)
	{
		printf("angle = %d\n", i);
		printf("%.0f %.0f\n", tan((PI * i) / 180) * 1000, ft_tan(i) * 1000);
		i++;
	}
	return (0);
}