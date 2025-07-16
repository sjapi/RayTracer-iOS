/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 032zolotarev <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 21:29:34 by 032zolotarev      #+#    #+#             */
/*   Updated: 2025/07/15 13:40:25 by 032zolotarev     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "minirt.h"
#include "renderer.h"
#include "utils.h"
#include <math.h>

bool	sphere_checkerboard(t_vec3 hit_point, t_obj *sphere)
{
	t_vec3	normal;
	float	longitude;
	float	latitude;
	int		cell_x_i;
	int		cell_y_i;

	normal = v_normalize(v_sub(hit_point, sphere->center));
	longitude  = 0.5f + (atan2f(normal.z, normal.x) / (2 * M_PI));
	latitude = 0.5f - (asinf(normal.y) / M_PI);
	if (sphere->selected)
	{
		cell_x_i = (int)(longitude * CHECKER_X_COUNT * 2);
		cell_y_i = (int)(latitude * CHECKER_Y_COUNT * 2);
	}
	else
	{
		cell_x_i = (int)(longitude * CHECKER_X_COUNT);
		cell_y_i = (int)(latitude * CHECKER_Y_COUNT);
	}
	return ((cell_x_i + cell_y_i) % 2 == 0);
}

bool cylinder_checkerboard(t_vec3 hit_point, t_obj *cyl, bool base)
{
	t_vec3	axis;
	t_vec3	diff;
	t_vec3	local;
	t_vec3	tangent;
	t_vec3	bitangent;
	t_vec3	base_center;
	float	radius;
	float	norm_rad;
	float	theta;
	float	height;
	float	x_local;
	float	y_local;
	int		cell_x_i;
	int		cell_y_i;


	axis = cyl->norm_vector;
	diff = v_sub(hit_point, cyl->center);

	if (base)
	{
		if (v_dot(diff, axis) > cyl->attrs[CYLINDER_H_I] * 0.5f)
			base_center = v_add(cyl->center, v_scale(axis, cyl->attrs[CYLINDER_H_I]));
		else
			base_center = cyl->center;
		diff = v_sub(hit_point, base_center);
		if (fabsf(axis.x) > 0.1f)
			tangent = v_normalize(v_cross((t_vec3){0, 1, 0}, axis));
		else
			tangent = v_normalize(v_cross((t_vec3){1, 0, 0}, axis));
		bitangent = v_cross(axis, tangent);
		x_local = v_dot(diff, tangent);
		y_local = v_dot(diff, bitangent);
		radius = cyl->attrs[CYLINDER_D_I] / 2.0f;
		norm_rad = sqrtf(x_local * x_local + y_local * y_local) / radius;
		if (norm_rad > 1)
			norm_rad = 1;
		theta = 0.5f + (atan2f(y_local, x_local) / (2 * M_PI));
		if (cyl->selected)
		{
			cell_x_i = (int)(theta * CHECKER_X_COUNT * 2);
			cell_y_i = (int)(norm_rad * 1);
		}
		else
		{
			cell_x_i = (int)(theta * CHECKER_X_COUNT);
			cell_y_i = (int)(norm_rad * 1);
		}
		return ((cell_x_i + cell_y_i) % 2 == 1);
	}
	else
	{
		height = v_dot(diff, axis);
		local = v_sub(diff, v_scale(axis, height));
		if (fabsf(axis.x) > 0.1f)
			tangent = v_normalize(v_cross((t_vec3){0, 1, 0}, axis));
		else
			tangent = v_normalize(v_cross((t_vec3){1, 0, 0}, axis));
		bitangent = v_cross(axis, tangent);
		x_local = v_dot(local, tangent);
		y_local = v_dot(local, bitangent);
		theta = 0.5f + (atan2f(y_local, x_local) / (2 * M_PI));
		height = height / cyl->attrs[CYLINDER_H_I];
		if (height < 0)
			height = 0;
		if (height > 1)
			height = 1;
		if (cyl->selected)
		{
			cell_x_i = (int)(theta * CHECKER_X_COUNT * 2);
			cell_y_i = (int)(height * CHECKER_Y_COUNT * 2);
		}
		else
		{
			cell_x_i = (int)(theta * CHECKER_X_COUNT);
			cell_y_i = (int)(height * CHECKER_Y_COUNT);
		}
		return ((cell_x_i + cell_y_i) % 2 == 0);
	}
}

bool	plane_checkerboard(t_vec3 hit_point, t_obj *plane)
{
	t_vec3	local;
	t_vec3	ortog_x;
	t_vec3	ortog_y;
	float	u, v;
	int		x, y;

	local = v_sub(hit_point, plane->center);

	ortog_x = v_cross((t_vec3){0.0f, 1.0f, 0.0f}, plane->norm_vector);
	if (v_len(ortog_x) < 1e-3f)
		ortog_x = v_cross((t_vec3){0.0f, 0.0f, 1.0f}, plane->norm_vector);
	ortog_x = v_normalize(ortog_x);
	ortog_y = v_normalize(v_cross(plane->norm_vector, ortog_x));

	u = v_dot(local, ortog_x);
	v = v_dot(local, ortog_y);
	if (plane->selected)
	{
		x = (int)floorf(u / (CHECKER_CELL_SIZE * 2));
		y = (int)floorf(v / (CHECKER_CELL_SIZE * 2));
	}
	else
	{
		x = (int)floorf(u / CHECKER_CELL_SIZE);
		y = (int)floorf(v / CHECKER_CELL_SIZE);
	}
	return ((x + y) % 2 == 0);
}

bool	cone_checkerboard(t_vec3 hit_point, t_obj *cone, bool base)
{
	t_vec3	axis;
	t_vec3	diff;
	t_vec3	tangent;
	t_vec3	bitangent;
	t_vec3	radial;
	float	angle_rad;
	float	radius_base;
	float	u;
	float	v;
	float	h;
	float	theta;
	float	v_tex;
	int		cell_x_i;
	int		cell_y_i;

	axis = cone->norm_vector;
	angle_rad = cone->attrs[CONE_AR_I];
	radius_base = tanf(angle_rad) * cone->attrs[CONE_H_I];
	if (fabsf(axis.x) > 0.1f)
		tangent = v_normalize(v_cross((t_vec3){0, 1, 0}, axis));
	else
		tangent = v_normalize(v_cross((t_vec3){1, 0, 0}, axis));
	bitangent = v_cross(axis, tangent);
	if (base)
	{
		diff = v_sub(hit_point, cone->center);
		u = v_dot(diff, tangent);
		v = v_dot(diff, bitangent);
		theta = 0.5f + atan2f(v, u) / (2 * M_PI);
		radial = (t_vec3){u, v, 0};
		v_tex = v_len(radial) / radius_base;
		if (v_tex > 1)
			v_tex = 1;
		if (cone->selected)
		{
			cell_x_i = (int)(theta * CHECKER_X_COUNT * 2);
			cell_y_i = (int)(v_tex * 1);
		}
		else
		{
			cell_x_i = (int)(theta * CHECKER_X_COUNT);
			cell_y_i = (int)(v_tex * 1);
		}
		return ((cell_x_i + cell_y_i) % 2 == 1);
	}
	else
	{
		diff = v_sub(hit_point, cone->center);
		h = v_dot(diff, axis);
		radial = v_sub(diff, v_scale(axis, h));
		u = v_dot(radial, tangent);
		v = v_dot(radial, bitangent);
		theta = 0.5f + atan2f(v, u) / (2 * M_PI);
		v_tex = (cone->attrs[CONE_H_I] - h) / cone->attrs[CONE_H_I];
		if (v_tex < 0)
			v_tex = 0;
		if (v_tex > 1)
			v_tex = 1;
		if (cone->selected)
		{
			cell_x_i = (int)(theta * CHECKER_X_COUNT * 2);
			cell_y_i = (int)(v_tex * CHECKER_Y_COUNT * 2);
		}
		else
		{
			cell_x_i = (int)(theta * CHECKER_X_COUNT);
			cell_y_i = (int)(v_tex * CHECKER_Y_COUNT);
		}
		return ((cell_x_i + cell_y_i) % 2 == 0);
	}
}
