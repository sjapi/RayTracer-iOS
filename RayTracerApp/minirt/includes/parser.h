/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:00:29 by haaghaja          #+#    #+#             */
/*   Updated: 2025/07/15 21:43:17 by 032zolotarev     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include "minirt.h"

/* parser.c */
t_scene	*load_scene(char *file_name);
bool	print_err(char *msg);
void	free_obj(t_obj *obj);
bool	append_obj(t_scene *scene, t_obj *obj);

/* parser_utils.c */
bool	is_valid_name(char *file_name);
bool	is_whitespace(char c);
bool	is_correct_coordinate(char *str);
bool	is_correct_color(char *str);
bool	is_int(char *num);
bool	is_float(char *num);
bool	is_checkerboard(char *str);
bool	is_mirror(char *str);

void	next_info(char **data);
void	skip_spaces(char **str);
bool	skip_integer(char **str, int *digits);

bool	parse_float(char **str, int *digits);

/* parser_tools.c */
bool	get_color(char *obj_data, int *num);
bool	get_coordinates(char *data, t_vec3 *p);
bool	get_orientation(char *data, t_vec3 *o);
bool	get_ratio(char *data, float *ratio);
bool	get_fov(char *data, int *fov);
bool	get_attribute(char *data, float *d);
bool	get_file_name(char *obj_data, char **name);

/* parse_elements.c */
bool	parse_ambient(char *light_data, t_scene *scene);
bool	parse_light(char *light_data, t_scene *scene);
bool	parse_camera(char *camera_data, t_scene *scene);

/* parse_objects.c */
bool	parse_obj(char *obj_data, t_scene *scene);
bool	parse_cylinder(char *cylinder_data, t_obj *cylinder);
bool	parse_sphere(char *sphere_data, t_obj *sphere);
bool	parse_plane(char *plane_data, t_obj *plane);

#endif
