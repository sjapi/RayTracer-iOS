/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:43:55 by azolotar          #+#    #+#             */
/*   Updated: 2025/07/15 19:20:42 by 032zolotarev     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "defines.h"
#include "utils.h"
#include <math.h>

void img_put_pixel_safe(t_rt *info, int x, int y, int color)
{
    char *pixel;

    if (x < 0 || x >= info->width)
        return;
    if (y < 0 || y >= info->height)
        return;

    pixel = info->addr + (info->line_len * y + x * (info->bpp / 8));
    pixel[0] = (color >> 16) & 0xFF;  // R
    pixel[1] = (color >> 8) & 0xFF;   // G
    pixel[2] = color & 0xFF;          // B
    pixel[3] = 255;                   // A
}

void	img_draw_line(t_rt *info, t_vec3 a, t_vec3 b, int color)
{
	float	dx;
	float	dy;
	int		sx;
	int		sy;
	float	err;
	float	e2;
	int		x0 = a.x;
	int		y0 = a.y;
	int		x1 = b.x;
	int		y1 = b.y;

	dx = ft_abs(x1 - x0);
	dy = -ft_abs(y1 - y0);
	sx = (x0 < x1) ? 1 : -1;
	sy = (y0 < y1) ? 1 : -1;
	err = dx + dy;

	while (1)
	{
		img_put_pixel_safe(info, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}
