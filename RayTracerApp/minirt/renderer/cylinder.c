/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 032zolotarev <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:56:16 by 032zolotarev      #+#    #+#             */
/*   Updated: 2025/07/15 13:32:22 by 032zolotarev     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "renderer.h"
#include "utils.h"
#include "defines.h"
#include <math.h>

t_vec3 get_cylinder_normal(t_obj *obj, t_vec3 hit_point, t_vec3 ray_dir, char side)
{
	t_vec3	v;
	float	h;
	t_vec3	n;
	t_vec3	normal;

	if (side == HIT_TOP)
		normal = obj->norm_vector;
	else if (side == HIT_BOTTOM)
		normal = v_scale(obj->norm_vector, -1);
	else
	{
		v = v_sub(hit_point, obj->center);
		h = v_dot(v, obj->norm_vector);
		n = v_sub(v, v_scale(obj->norm_vector, h));
		normal = v_normalize(n);
	}
	if (v_dot(normal, ray_dir) > 0)
		normal = v_scale(normal, -1);
	return normal;
}

static float intersect_surface(t_ray *ray, t_obj *cyl)
{
	t_vec3 oc = v_sub(ray->origin, cyl->center);
	t_vec3 v = cyl->norm_vector;

	float radius = cyl->attrs[CYLINDER_D_I] / 2.0f;
	float height = cyl->attrs[CYLINDER_H_I];

	float dv = v_dot(ray->direction, v);
	float ocv = v_dot(oc, v);

	float A = v_dot(ray->direction, ray->direction) - dv * dv;
	float B = 2.0f * (v_dot(ray->direction, oc) - dv * ocv);
	float C = v_dot(oc, oc) - ocv * ocv - radius * radius;

	float disc = B * B - 4 * A * C;
	if (disc < 0)
		return -1.0f;

	float sqrt_disc = sqrtf(disc);
	float t1 = (-B - sqrt_disc) / (2 * A);
	float t2 = (-B + sqrt_disc) / (2 * A);

	float t = -1.0f;

	if (t1 > 0)
	{
		float m = ocv + t1 * dv;
		if (m >= 0 && m <= height)
			t = t1;
	}

	if (t2 > 0)
	{
		float m = ocv + t2 * dv;
		if (m >= 0 && m <= height)
		{
			if (t < 0 || t2 < t)
				t = t2;
		}
	}
	return t;
}

static float intersect_base(t_ray *ray, t_obj *cyl, int base)
{
	t_vec3 v = cyl->norm_vector;
	t_vec3 base_center = cyl->center;
	if (base == HIT_TOP)
		base_center = v_add(cyl->center, v_scale(v, cyl->attrs[CYLINDER_H_I]));

	float denom = v_dot(ray->direction, v);
	if (fabsf(denom) < 1e-6)
		return -1.0f; // Параллельно плоскости

	float t = v_dot(v_sub(base_center, ray->origin), v) / denom;
	if (t < 0)
		return -1.0f;

	t_vec3 p = v_add(ray->origin, v_scale(ray->direction, t));
	t_vec3 diff = v_sub(p, base_center);
	float dist_sq = v_dot(diff, diff);
	float radius = cyl->attrs[CYLINDER_D_I] / 2.0f;

	if (dist_sq <= radius * radius)
		return t;

	return -1.0f;
}

float	intersect_cylinder(t_ray *ray, t_obj *obj, char *side, bool *reverse)
{
	float	surface;
	float	top;
	float	bottom;
	float	t;

	surface = intersect_surface(ray, obj);
	top = intersect_base(ray, obj, HIT_TOP);
	bottom = intersect_base(ray, obj, HIT_BOTTOM);
	t = -1.0;
	if (surface > 0)
	{
		t = surface;
		*side = HIT_SURFACE;
	}
	if (bottom > 0 && (t < 0 || bottom < t))
	{
		t = bottom;
		*side = HIT_BOTTOM;
	}
	if (top > 0 && (t < 0 || top < t))
	{
		t = top;
		*side = HIT_TOP;
	}
	*reverse = false;
	if (t > 0 && (obj->checkerboard || obj->selected))
	{
		t_vec3 hit_point = v_add(ray->origin, v_scale(ray->direction, t));
		if (*side == HIT_SURFACE)
			*reverse = cylinder_checkerboard(hit_point, obj, false);
		else if (*side == HIT_TOP || *side == HIT_BOTTOM)
			*reverse = cylinder_checkerboard(hit_point, obj, true);
	}
	return (t);
}
