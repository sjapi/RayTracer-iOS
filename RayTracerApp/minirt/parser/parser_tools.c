/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:05:46 by haaghaja          #+#    #+#             */
/*   Updated: 2025/07/15 16:55:33 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "minirt.h"
#include "parser.h"
#include "utils.h"


bool	get_file_name(char *obj_data, char **name)
{
	int	size;
	char	*tmp;

	size = 0;
	while (obj_data[size] && !is_whitespace(obj_data[size]) && obj_data[size] != '\n')
		size++;
	if (size == 0)
		return (false);
	tmp = malloc(sizeof(char) * size);
	if (!tmp)
		return (print_err("Can't allocate memory"));
	tmp[size] = '\0';
	*name = tmp;
	while (size > 0)
	{
		*tmp = *obj_data;
		tmp++;
		obj_data++;
		size--;
	}
	// TODO: check for .xpm
	return (true);
}


bool	get_color(char *obj_data, int *color_code)
{
	int	n;

	if (!is_correct_color(obj_data))
		return (false);
	*color_code = 0;
	n = 0;
	while (*obj_data >= '0' && *obj_data <= '9')
		n = n * 10 + (*obj_data++ - '0');
	*color_code = n;
	n = 0;
	obj_data++;
	while (*obj_data >= '0' && *obj_data <= '9')
		n = n * 10 + (*obj_data++ - '0');
	*color_code = (*color_code << 8) | n;
	n = 0;
	obj_data++;
	while (*obj_data >= '0' && *obj_data <= '9')
		n = n * 10 + (*obj_data++ - '0');
	*color_code = (*color_code << 8) | n;
	return (true);
}

bool	get_coordinates(char *data, t_vec3 *p)
{
	if (!is_correct_coordinate(data))
		return (false);
	p->x = ft_atof(data);
	while (*data && *data != ',')
		data++;
	data++;
	p->y = ft_atof(data);
	while (*data && *data != ',')
		data++;
	data++;
	p->z = ft_atof(data);
	return (true);
}

bool	get_orientation(char *data, t_vec3 *o)
{
	if (!is_correct_coordinate(data))
		return (false);
	o->x = ft_atof(data);
	while (*data && *data != ',')
		data++;
	data++;
	o->y = ft_atof(data);
	while (*data && *data != ',')
		data++;
	data++;
	o->z = ft_atof(data);
	if (o->x < -1.0 || o->x > 1.0
		|| o->y < -1.0 || o->y > 1.0
		|| o->z < -1.0 || o->z > 1.0)
		return (false);
	return (true);
}

bool	get_ratio(char *data, float *ratio)
{
	if (!is_float(data))
		return (false);
	*ratio = ft_atof(data);
	if (*ratio < 0.0 || *ratio > 1.0)
		return (false);
	return (true);
}

bool	get_fov(char *data, int *fov)
{
	if (!is_int(data))
		return (false);
	*fov = ft_atoi(data);
	if (*fov < 0 || *fov > 180)
		return (false);
	return (true);
}

bool	get_attribute(char *data, float *attr)
{
	if (!is_float(data))
		return (false);
	*attr = ft_atof(data);
	if (*attr < 0.0)
		return (false);
	return (true);
}
