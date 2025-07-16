/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 032zolotarev <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:54:16 by 032zolotarev      #+#    #+#             */
/*   Updated: 2025/07/15 13:31:45 by 032zolotarev     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "renderer.h"
#include "utils.h"
#include <math.h>

float	intersect_plane(t_ray *ray, t_obj *plane, bool *reverse)
{
	float	denom;
	float	t;
	t_vec3	hit_point;

	denom = v_dot(ray->direction, plane->norm_vector);
	if (fabsf(denom) < 1e-6)
		return (-1);
	t = v_dot(v_sub(plane->center, ray->origin), plane->norm_vector) / denom;
	if (t < 0)
		return (-1);
	hit_point = v_add(ray->origin, v_scale(ray->direction, t));
	if (plane->checkerboard || plane->selected)
		*reverse = plane_checkerboard(hit_point, plane);
	return (t);
}
