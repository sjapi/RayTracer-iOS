/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:36:01 by azolotar          #+#    #+#             */
/*   Updated: 2025/07/14 18:41:00 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "defines.h"
#include "utils.h"
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

void free_optimization(t_optim *optim)
{
    if (!optim)
        return;
    free(optim->viewport_x);
    free(optim->viewport_y);
    free(optim);
}

static t_optim	*alloc_optim(t_rt *info)
{
	t_optim *optim;

	optim = malloc(sizeof(t_optim));
	if (!optim)
		return (NULL);
	optim->viewport_x = malloc(sizeof(float) * info->width);
	if (!optim->viewport_x)
	{
		free(optim);
		return (NULL);
	}
	optim->viewport_y = malloc(sizeof(float) * info->height);
	if (!optim->viewport_y)
	{
		free(optim->viewport_x);
		free(optim);
		return (NULL);
	}
	return (optim);
}

float	get_nx(int x, float aspect_ratio, float tan_fov, float width)
{
	float	nx;

	nx = (float)(x + 0.5) / (float)width;
	nx = (2.0 * nx - 1.0) * aspect_ratio * tan_fov;
	return (nx);
}

float	get_ny(int y, float tan_fov, float height)
{
	float	ny;

	ny = (float)(y + 0.5) / (float)height;
	ny = (1.0 - 2.0 * ny) * tan_fov;
	return (ny);
}

static void	optimize_viewport(t_rt *info, t_optim *optim)
{
	float	tan_fov;
	int		x;
	int		y;

	tan_fov = tanf((info->scene->cam->fov * M_PI / 180.0) / 2.0);
	x = 0;
	while (x < info->width)
	{
		optim->viewport_x[x] = get_nx(x, info->win_aspect_ratio, tan_fov, info->width);
		x++;
	}
	y = 0;
	while (y < info->height)
	{
        optim->viewport_y[y] = get_ny(y, tan_fov, info->height);
		y++;
	}
}

static void	optimize_cone(t_obj *cone)
{
	t_vec3	apex;
	float	angle_rad;

	apex = v_add(cone->center, v_scale(cone->norm_vector, cone->attrs[CONE_H_I]));
	cone->attrs[CONE_AP_X_I] = apex.x;
	cone->attrs[CONE_AP_Y_I] = apex.y;
	cone->attrs[CONE_AP_Z_I] = apex.z;
	angle_rad = cone->attrs[CONE_A_I] * M_PI / 180.0;
	cone->attrs[CONE_AR_I] = angle_rad;
	cone->attrs[CONE_TAN2] = tanf(angle_rad) * tanf(angle_rad);
	cone->attrs[CONE_COS2] = cosf(angle_rad) * cosf(angle_rad);
}

static void	optimize_cylinder(t_obj *cylinder)
{
	(void)cylinder;
}

static void	optimize_objs(t_rt *info)
{
	int		i;
	t_obj	*obj;

	i = 0;
	while (i < info->scene->objs_count)
	{
		obj = &info->scene->objs[i];
		if (obj->type == CONE)
			optimize_cone(obj);
		else if (obj->type == CYLINDER)
			optimize_cylinder(obj);
		else if (obj->type == SPHERE)
			obj->attrs[SPHERE_R_I] = obj->attrs[SPHERE_D_I] * 0.5;
		i++;
	}
}

static void	optimize_cam_basis(t_cam *cam)
{
	t_vec3  world_up;

	if (fabsf(cam->orient_v.x) < 1e-6 && fabsf(cam->orient_v.z) < 1e-6)
		world_up = (t_vec3){0, 0, 1};
	else
		world_up = (t_vec3){0, 1, 0};
	cam->right = v_normalize(v_cross(world_up, cam->orient_v));
	cam->up = v_cross(cam->orient_v, cam->right);
}

bool	init_optimization(t_rt *info)
{
	t_optim *optim;

	optim = alloc_optim(info);
	if (!optim)
		return (false);
	optimize_viewport(info, optim);
	optimize_objs(info);
	optimize_cam_basis(info->scene->cam);
	info->optim = optim;
	return (true);
}
