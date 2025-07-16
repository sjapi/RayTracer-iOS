/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 032zolotarev <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:34:24 by 032zolotarev      #+#    #+#             */
/*   Updated: 2025/07/15 13:32:05 by 032zolotarev     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "renderer.h"
#include "utils.h"
#include "defines.h"
#include <math.h>

t_vec3 get_cone_normal(t_obj *obj, t_vec3 hit_point, t_vec3 ray_dir, char side)
{
	t_vec3	apex;
	t_vec3	normal;
	t_vec3	x;
	t_vec3	n;
	float	m;

	apex = (t_vec3){
		obj->attrs[CONE_AP_X_I],
		obj->attrs[CONE_AP_Y_I],
		obj->attrs[CONE_AP_Z_I]
	};
	if (side == HIT_BOTTOM)
	{
		normal = obj->norm_vector;
	}
	else
	{
		x = v_sub(hit_point, apex);
		m = v_dot(obj->norm_vector, x);
		n = v_sub(x, v_scale(obj->norm_vector, (1 + obj->attrs[CONE_TAN2]) * m));
		normal = v_normalize(n);
	}
	if (v_dot(normal, ray_dir) > 0)
		normal = v_scale(normal, -1);
	return (normal);
}

static float intersect_cone_base(t_ray *ray, t_obj *obj)
{
	t_vec3	apex;
	t_vec3	base_center;
	float	denom;
	float	t;
	t_vec3	p;
	t_vec3	diff;
	float	radius;
	float	dist_sq;

	apex = (t_vec3){
		obj->attrs[CONE_AP_X_I],
		obj->attrs[CONE_AP_Y_I],
		obj->attrs[CONE_AP_Z_I]
	};
	base_center = v_sub(apex, v_scale(obj->norm_vector, obj->attrs[CONE_H_I]));
	denom = v_dot(ray->direction, obj->norm_vector);
	if (fabsf(denom) < 1e-6)
		return (-1.0);
	t = v_dot(v_sub(base_center, ray->origin), obj->norm_vector) / denom;
	if (t < 0.0f)
		return (-1.0);
	p = v_add(ray->origin, v_scale(ray->direction, t));
	diff = v_sub(p, base_center);
	radius = obj->attrs[CONE_H_I] * tanf(obj->attrs[CONE_AR_I]);
	dist_sq = v_dot(diff, diff);
	if (dist_sq <= radius * radius)
		return t;
	return (-1.0);
}

static float intersect_cone_surface(t_ray *ray, t_obj *obj)
{
	t_vec3	apex;
	t_vec3	co;
	t_vec3 	v;
	float 	dv;
	float 	cov;
	float 	cos2a;
	float 	A;
	float 	B;
	float 	C;
	float 	discrim;
	float 	sqrt_disc;
	float 	t1;
	float 	t2;
	float 	t;
	t_vec3	p;
	float	h;

	apex = (t_vec3){
		obj->attrs[CONE_AP_X_I],
		obj->attrs[CONE_AP_Y_I],
		obj->attrs[CONE_AP_Z_I]
	};
	co = v_sub(ray->origin, apex);
	v = obj->norm_vector;
	dv = v_dot(ray->direction, v);
	cov = v_dot(co, v);
	cos2a = obj->attrs[CONE_COS2];
	A = v_dot(ray->direction, ray->direction) - (dv * dv) / cos2a;
	B = 2.0f * (v_dot(ray->direction, co) - (dv * cov) / cos2a);
	C = v_dot(co, co) - (cov * cov) / cos2a;
	discrim = B * B - 4.0f * A * C;
	if (discrim < 0.0f)
		return (-1.0);
	sqrt_disc = sqrtf(discrim);
	t1 = (-B - sqrt_disc) / (2.0f * A);
	t2 = (-B + sqrt_disc) / (2.0f * A);
	t = -1.0f;
	if (t1 > 0.0f)
		t = t1;
	if (t2 > 0.0f && (t < 0.0f || t2 < t))
		t = t2;
	if (t < 0.0f)
		return (-1.0);
	p = v_add(ray->origin, v_scale(ray->direction, t));
	h = v_dot(v_sub(apex, p), v);
	if (h < 0.0f || h > obj->attrs[CONE_H_I])
		return (-1.0);
	return (t);
}

float intersect_cone(t_ray *ray, t_obj *obj, char *side, bool *reverse)
{
	float	surface;
	float	base;
	float	t;
	t_vec3	hit_point;

	surface = intersect_cone_surface(ray, obj);
	base = intersect_cone_base(ray, obj);
	t = -1.0;
	if (surface > 0)
	{
		t = surface;
		*side = HIT_SURFACE;
	}
	if (base > 0 && (t < 0 || base < t))
	{
		t = base;
		*side = HIT_BOTTOM;
	}
	if (t > 0 && (obj->checkerboard || obj->selected))
	{
		hit_point = v_add(ray->origin, v_scale(ray->direction, t));
		*reverse = cone_checkerboard(hit_point, obj, *side == HIT_BOTTOM);
	}
	return (t);
}
