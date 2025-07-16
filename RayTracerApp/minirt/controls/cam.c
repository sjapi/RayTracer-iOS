/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 032zolotarev <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:02:45 by 032zolotarev      #+#    #+#             */
/*   Updated: 2025/07/15 20:10:30 by 032zolotarev     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "minirt.h"
#include "utils.h"
#include <math.h>
#include <stdbool.h>

bool translate_cam(t_cam *cam, int key)
{
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;
	float	val;

	val = 0.4f;
	forward = v_normalize(cam->orient_v);
	right = v_normalize(v_cross((t_vec3){0, 1, 0}, forward));
	up = (t_vec3){0, 1, 0};
	if (key == KEY_W)
    cam->viewpoint = v_add(cam->viewpoint, v_scale(forward, val));
	else if (key == KEY_S)
		cam->viewpoint = v_sub(cam->viewpoint, v_scale(forward, val));
	else if (key == KEY_A)
    	cam->viewpoint = v_sub(cam->viewpoint, v_scale(right, val));
	else if (key == KEY_D)
    	cam->viewpoint = v_add(cam->viewpoint, v_scale(right, val));
	else if (key == KEY_Q)
    	cam->viewpoint = v_sub(cam->viewpoint, v_scale(up, val));
	else if (key == KEY_E)
    	cam->viewpoint = v_add(cam->viewpoint, v_scale(up, val));
	else
    	return (false);
	return (true);
}

bool	rotate_cam(t_cam *cam, int key)
{
	if (key == KEY_H)
		cam->yaw -= 0.1;
	else if (key == KEY_L)
		cam->yaw += 0.1;
	else if (key == KEY_J)
		cam->pitch += 0.1;
	else if (key == KEY_K)
		cam->pitch -= 0.1;
	else
		return (false);
	cam->pitch = clampf(cam->pitch, -1.55, 1.55);
	cam->orient_v.x = cosf(cam->pitch) * sinf(cam->yaw);
	cam->orient_v.y = sinf(cam->pitch);
	cam->orient_v.z = cosf(cam->pitch) * cosf(cam->yaw);
	return (true);

}
