/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 032zolotarev <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 10:30:53 by 032zolotarev      #+#    #+#             */
/*   Updated: 2025/07/07 10:55:19 by 032zolotarev     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

/*
 * need to call this func only ONCE, before each 'rendering'
 */
int	get_amb_color(t_amb_light *amb)
{
	int	r;
	int	g;
	int	b;

	r = (amb->color >> 16) & 0xff;
	g = (amb->color >> 8) & 0xff;
	b = amb->color & 0xff;
	r = (int)fmin((float)r * amb->ratio, 255.0);
	g = (int)fmin((float)g * amb->ratio, 255.0);
	b = (int)fmin((float)b * amb->ratio, 255.0);
	return ((r << 16) | (g << 8) | b);
}
