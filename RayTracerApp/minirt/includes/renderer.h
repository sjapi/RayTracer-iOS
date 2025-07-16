/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:51:00 by azolotar          #+#    #+#             */
/*   Updated: 2025/07/15 19:24:28 by 032zolotarev     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

# include "minirt.h"
# include <stdbool.h>

/*
 * origin is position of cam
 */
typedef struct	s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

/*
 * t - distance from ray origin to hit point
 * hit_point - coords of hit
 * normal - ???
 * hit_object - hit object id
 * hit - hit or not
 * reverse - for checkerboard
 */
typedef struct	s_hit
{
	float		t;
	t_vec3	hit_point;
	t_vec3	normal;
	t_obj		*obj;
	char		side;
	bool		contour;
	bool		reverse;
}	t_hit;

/* optimization */
bool	init_optimization(t_rt *info);

/* render.c */
void	render_scene(t_rt *info);

/* draw.c */
void	img_put_pixel_safe(t_rt *info, int x, int y, int color);
void	img_draw_line(t_rt *info, t_vec3 a, t_vec3 b, int color);
void	draw_xyz_axis(t_rt *info);

/* ray.c */
void	init_ray(t_ray *ray, t_rt *info, int x, int y);

t_vec3	get_ray_dir(float nx, float ny, t_cam *cam);

/* hit.c */
bool	find_hit(t_ray *ray, t_rt *info, t_hit *hit, bool shadow);

/* intersection */
float	intersect_plane(t_ray *ray, t_obj *plane, bool *reverse);
float 	intersect_sphere(t_ray *ray, t_obj *sphere, bool *reverse);
float	intersect_cylinder(t_ray *ray, t_obj *cylinder, char *side, bool *reverse);
float	intersect_cone(t_ray *ray, t_obj *cone, char *side, bool *reverse);

/* normal */
t_vec3	get_cylinder_normal(t_obj *obj, t_vec3 hit_point, t_vec3 ray_dir, char side);
t_vec3	get_cone_normal(t_obj *obj, t_vec3 hit_point, t_vec3 ray_dir, char side);

/* checkerboard */
bool	sphere_checkerboard(t_vec3 hit_point, t_obj *sphere);
bool	cylinder_checkerboard(t_vec3 hit_point, t_obj *cyl, bool base);
bool	plane_checkerboard(t_vec3 hit_point, t_obj *plane);
bool	cone_checkerboard(t_vec3 hit_point, t_obj *cone, bool base);

/* info */
void	draw_info(t_rt *info);

#endif
