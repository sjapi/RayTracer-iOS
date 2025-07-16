/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 032zolotarev <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:49:48 by 032zolotarev      #+#    #+#             */
/*   Updated: 2025/07/14 18:38:21 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "utils.h"
#include "renderer.h"
#include <math.h>

t_vec3	get_ray_dir(float nx, float ny, t_cam *cam)
{
	t_vec3	dir;

	dir = v_add(
		v_add(cam->orient_v, v_scale(cam->right, nx)),
		v_scale(cam->up, ny)
	);
	return (v_normalize(dir));
}

/*
 * at first nx, ny - normalized coordinates in range 0...1
 * and after they are converted to range -1...1 and scaled to actual size of viewport
 */
void	init_ray(t_ray *ray, t_rt *info, int x, int y)
{
	float		nx;
	float		ny;

	nx = info->optim->viewport_x[x];
	ny = info->optim->viewport_y[y];
	ray->direction = get_ray_dir(nx, ny, info->scene->cam);
}
