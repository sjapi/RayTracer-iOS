/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 032zolotarev <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:55:36 by 032zolotarev      #+#    #+#             */
/*   Updated: 2025/07/15 19:08:39 by 032zolotarev     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "renderer.h"
#include "utils.h"
#include "defines.h"
#include <math.h>

float	intersect_sphere(t_ray *ray, t_obj *sphere, bool *reverse)
{
	float radius = sphere->attrs[SPHERE_R_I];
	t_vec3 oc = v_sub(ray->origin, sphere->center);

	float a = 1.0f; //v_dot(ray->direction, ray->direction);
	float b = 2.0f * v_dot(oc, ray->direction);
	float c = v_dot(oc, oc) - radius * radius;

	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);

	float sqrt_disc = sqrtf(discriminant);
	float t0 = (-b - sqrt_disc) / (2 * a);
	float t1 = (-b + sqrt_disc) / (2 * a);

	float t;
	if (t0 > 1e-6)
		t = t0;
	else if (t1 > 1e-6)
		t = t1;
	else
		return -1;
	t_vec3 hit_point = v_add(ray->origin, v_scale(ray->direction, t));
	if (sphere->checkerboard || sphere->selected)
		*reverse = sphere_checkerboard(hit_point, sphere);
	return (t);
}
