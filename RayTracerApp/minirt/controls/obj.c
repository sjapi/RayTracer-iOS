/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 032zolotarev <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:57:47 by 032zolotarev      #+#    #+#             */
/*   Updated: 2025/07/15 18:43:04 by 032zolotarev     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "defines.h"
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

bool	translate_obj(t_obj *obj, int key)
{
	float	val;

	val = 0.2;
	if (key == KEY_Q)
		obj->center.x += val;
	else if (key == KEY_A)
		obj->center.x -= val;
	else if (key == KEY_W)
		obj->center.y += val;
	else if (key == KEY_S)
		obj->center.y -= val;
	else if (key == KEY_E)
		obj->center.z += val;
	else if (key == KEY_D)
		obj->center.z -= val;
	else
		return (false);
	return (true);
}

bool	rotate_obj(t_obj *obj, int key)
{
	t_vec3	v;
	t_vec3	res;
	float	angle;

	v = obj->norm_vector;
	angle = 0.1f;
	if (key == KEY_X)
	{
		res.x = v.x;
		res.y = v.y * cosf(angle) - v.z * sinf(angle);
		res.z = v.y * sinf(angle) + v.z * cosf(angle);
	}
	else if (key == KEY_Y)
	{
		res.x = v.x * cosf(angle) + v.z * sinf(angle);
		res.y = v.y;
		res.z = -v.x * sinf(angle) + v.z * cosf(angle);
	}
	else if (key == KEY_Z)
	{
		res.x = v.x * cosf(angle) - v.y * sinf(angle);
		res.y = v.x * sinf(angle) + v.y * cosf(angle);
		res.z = v.z;
	}
	else
		return (false);
	obj->norm_vector = res;
	return (true);
}
