/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/04 13:28:15 by afaucher          #+#    #+#             */
/*   Updated: 2014/01/05 14:56:37 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS_H
# define MATHS_H
# define PI 3.14159265359
# define RAD(degree) (PI * degree) / 180
float	ft_pow(float nb, int p);
float	ft_abs(float nb);
long	ft_fact(long nb);
float	ft_cos(float rad);
float	ft_sin(float rad);
float	ft_tan(float rad);
#endif /* MATHS_H */
