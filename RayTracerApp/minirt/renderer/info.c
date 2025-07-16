/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 032zolotarev <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:29:57 by 032zolotarev      #+#    #+#             */
/*   Updated: 2025/07/15 19:30:23 by 032zolotarev     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "renderer.h"
#include "defines.h"
#include "utils.h"

void	draw_xyz_axis(t_rt *info)
{
	t_vec3	origin;
	t_vec3	x_end;
	t_vec3	y_end;
	t_vec3	z_end;
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;
	float	len;

	len = 50.0f;
	origin = (t_vec3){10 + len, 40 + len, 0};

	forward = v_normalize(info->scene->cam->orient_v);
	right = v_normalize(v_cross(forward, (t_vec3){0, 1, 0}));
	up = v_normalize(v_cross(right, forward));

	// Проекции на экран — только X и Y
	x_end.x = origin.x + right.x * len;
	x_end.y = origin.y - right.y * len; // минус — т.к. экран y вниз
	x_end.z = 0;

	y_end.x = origin.x + up.x * len;
	y_end.y = origin.y - up.y * len;
	y_end.z = 0;

	z_end.x = origin.x + forward.x * len;
	z_end.y = origin.y - forward.y * len;
	z_end.z = 0;

	img_draw_line(info, origin, x_end, 0xff0000); // X — красный
	img_draw_line(info, origin, y_end, 0x00ff00); // Y — зелёный
	img_draw_line(info, origin, z_end, 0x0000ff); // Z — синий
}

void	draw_info(t_rt *info)
{
}
