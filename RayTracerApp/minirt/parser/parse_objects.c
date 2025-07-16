/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:21:58 by haaghaja          #+#    #+#             */
/*   Updated: 2025/07/15 16:47:03 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include "parser.h"
#include "defines.h"
#include "utils.h"


bool	parse_texture(char **obj_data, t_obj *obj)
{
	if (!**obj_data || **obj_data == '\n')
		return (true);	
	if (is_checkerboard(*obj_data))
		obj->checkerboard = true;
	else if (is_mirror(*obj_data))
		obj->mirror = true;
	else
		return (print_err("Invalid file name"));
	next_info(obj_data);
	return (true);
}


bool	parse_plane(char *plane_data, t_obj *plane)
{
	plane->type = PLANE;
	next_info(&plane_data);
	if (!get_coordinates(plane_data, &plane->center))
		return (free_obj(plane), print_err("Plane has invalid coordinates"));
	next_info(&plane_data);
	if (!get_orientation(plane_data, &plane->norm_vector))
		return (free_obj(plane), print_err("Plane has invalid orientation"));
	next_info(&plane_data);
	if (!get_color(plane_data, &plane->color))
		return (free_obj(plane), print_err("Plane has invalid color"));
	next_info(&plane_data);
	parse_texture(&plane_data, plane);
	if (*plane_data && *plane_data != '\n')
		return (free_obj(plane), print_err("Plane has invalid data"));
	return (true);
}

bool	parse_sphere(char *sphere_data, t_obj *sphere)
{
	sphere->type = SPHERE;
	sphere->attrs = malloc(sizeof(float) * SPHERE_ATTR_COUNT);
	if (!sphere->attrs)
		return (free_obj(sphere), print_err("Can't allocate memory"));	
	next_info(&sphere_data);
	if (!get_coordinates(sphere_data, &sphere->center))
		return (free_obj(sphere), print_err("Sphere has invalid coordinates"));
	next_info(&sphere_data);
	if (!get_attribute(sphere_data, &sphere->attrs[SPHERE_D_I]))
		return (free_obj(sphere), print_err("Sphere has invalid diameter"));
	next_info(&sphere_data);
	if (!get_color(sphere_data, &sphere->color))
		return (free_obj(sphere), print_err("Sphere has invalid color"));
	next_info(&sphere_data);
	parse_texture(&sphere_data, sphere);
	if (*sphere_data && *sphere_data != '\n')
		return (free_obj(sphere), print_err("Sphere has invalid data"));
	return (true);
}

bool	parse_cylinder(char *cylinder_data, t_obj *cylinder)
{
	cylinder->type = CYLINDER;
	cylinder->attrs = malloc(sizeof(float) * CYLINDER_ATTR_COUNT);
	if (!cylinder->attrs)
		return (free_obj(cylinder), print_err("Can't allocate memory"));	
	next_info(&cylinder_data);
	if (!get_coordinates(cylinder_data, &cylinder->center))
		return (free_obj(cylinder), print_err("Cylinder has invalid coordinates"));
	next_info(&cylinder_data);
	if (!get_orientation(cylinder_data, &cylinder->norm_vector))
		return (free_obj(cylinder), print_err("Cylinder has invalid orientation"));
	next_info(&cylinder_data);
	if (!get_attribute(cylinder_data, &cylinder->attrs[CYLINDER_D_I]))
		return (free_obj(cylinder), print_err("Cylinder has invalid diameter"));
	next_info(&cylinder_data);
	if (!get_attribute(cylinder_data, &cylinder->attrs[CYLINDER_H_I]))
		return (free_obj(cylinder), print_err("Cylinder has invalid height"));
	next_info(&cylinder_data);
	if (!get_color(cylinder_data, &cylinder->color))
		return (free_obj(cylinder), print_err("Cylinder has invalid color"));
	next_info(&cylinder_data);
	parse_texture(&cylinder_data, cylinder);
	if (*cylinder_data && *cylinder_data != '\n')
		return (free_obj(cylinder), print_err("Cylinder has invalid data"));
	return (true);
}

/*
 * co     0,0,0   0,1,0   30         5      255,0,0
 *        center  norm    half_angle height color
 */
bool	parse_cone(char *cone_data, t_obj *cone)
{
	cone->type = CONE;
	cone->attrs = malloc(sizeof(float) * CONE_ATTR_COUNT);
	if (!cone->attrs)
		return (free_obj(cone), print_err("Can't allocate memory"));	
	next_info(&cone_data);
	if (!get_coordinates(cone_data, &cone->center))
		return (free_obj(cone), print_err("Cone has invalid coordinates"));
	next_info(&cone_data);
	if (!get_orientation(cone_data, &cone->norm_vector))
		return (free_obj(cone), print_err("Cone has invalid orientation"));
	next_info(&cone_data);
	if (!get_attribute(cone_data, &cone->attrs[CONE_A_I]))
		return (free_obj(cone), print_err("Cone has invalid angle"));
	next_info(&cone_data);
	if (!get_attribute(cone_data, &cone->attrs[CONE_H_I]))
		return (free_obj(cone), print_err("Cone has invalid height"));
	next_info(&cone_data);
	if (!get_color(cone_data, &cone->color))
		return (free_obj(cone), print_err("Cone has invalid color"));
	next_info(&cone_data);
	parse_texture(&cone_data, cone);
	if (*cone_data && *cone_data != '\n')
		return (free_obj(cone), print_err("Cone has invalid data"));
	return (true);
}

/*
 * Here you can just do 'return (parse_plane(...))'
 */
bool	parse_obj(char *obj_data, t_scene *scene)
{
	t_obj	*obj;

	obj = ft_calloc(sizeof(t_obj), 1);
	if (!obj)
		return (print_err("Can't allocate memory"));
	if (ft_strncmp(obj_data, "pl ", 3) == 0)
	{
		if (!parse_plane(obj_data, obj))
			return (false);
	}
	else if (ft_strncmp(obj_data, "sp ", 3) == 0)
	{
		if (!parse_sphere(obj_data, obj))
			return (false);
	}
	else if (ft_strncmp(obj_data, "cy ", 3) == 0)
	{
		if (!parse_cylinder(obj_data, obj))
			return (false);
		obj->bounding_r = sqrt(pow(obj->attrs[CYLINDER_H_I], 2) + pow(obj->attrs[CYLINDER_D_I], 2));
	}
	else if (ft_strncmp(obj_data, "co ", 3) == 0)
	{
		if (!parse_cone(obj_data, obj))
			return (false);
	}
	else
		return (true); // TODO: unkown type	
	return (append_obj(scene, obj));
}
