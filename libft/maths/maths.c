/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/04 13:23:28 by afaucher          #+#    #+#             */
/*   Updated: 2014/01/05 14:35:14 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"
#include "../libft.h"

float		ft_pow(float nb, int p)
{
	if (p == 0)
		return (1);
	return (nb * ft_pow(nb, p - 1));
}

long	ft_fact(long nb)
{
	if (nb == 0)
		return (1);
	if (nb < 20 && nb > 0)
		return (nb * ft_fact(nb - 1));
	return (0);
}

float		ft_cos(float rad)
{
	float	acc;
	int		con;
	int		nb;
	float	cos;

	nb = 0;
	con = -1;
	cos = 1;
	acc = 0.001;
	while (ft_abs(ft_pow(rad, 1 + nb) / ft_fact(1 + nb)) >= acc)
	{
		cos += con * (ft_pow(rad, 2 + nb) / ft_fact(2 + nb));
		con *= -1;
		nb += 2;
	}
	return (cos);
}

float		ft_sin(float rad)
{
	float	acc;
	int		con;
	int		nb;
	float	sin;

	nb = 1;
	con = -1;
	acc = 0.001;
	sin = rad;
	while (ft_abs(ft_pow(rad, 1 + nb) / ft_fact(1 + nb)) >= acc)
	{
		sin += con * (ft_pow(rad, 2 + nb) / ft_fact(2 + nb));
		con *= -1;
		nb += 2;
	}
	return (sin);
}

float		ft_tan(float rad)
{
	return (ft_sin(rad) / ft_cos(rad));
}
