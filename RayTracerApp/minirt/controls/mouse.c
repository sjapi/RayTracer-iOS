/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 032zolotarev <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:49:50 by 032zolotarev      #+#    #+#             */
/*   Updated: 2025/07/15 12:56:16 by 032zolotarev     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"
#include "renderer.h"
#include "utils.h"

t_obj	*mouse_click_obj(int button, int x, int y, t_rt *info)
{
	t_ray	ray;
	t_hit	hit;
	float	tan_fov;
	float	nx;
	float	ny;

	tan_fov = tanf(info->scene->cam->fov * 0.5f * M_PI / 180.0f);
	nx = get_nx(x, info->win_aspect_ratio, tan_fov, info->width);
	ny = get_ny(y, tan_fov, info->height);
	ray.origin = info->scene->cam->viewpoint;
	ray.direction = get_ray_dir(nx, ny, info->scene->cam);
	if (find_hit(&ray, info, &hit, false))
		return (hit.obj);
	else
		return (NULL);
}
