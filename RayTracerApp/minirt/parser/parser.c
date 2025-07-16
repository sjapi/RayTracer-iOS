/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:01:55 by haaghaja          #+#    #+#             */
/*   Updated: 2025/07/15 13:12:35 by 032zolotarev     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include "parser.h"
#include "utils.h"
#include "get_next_line.h"
#include "defines.h"

bool	print_err(char *msg)
{
	printf("Error\n");
	printf("miniRT: parser: %s\n", msg);
	return (false);
}

void	free_obj(t_obj *obj)
{
	if (obj->attrs)
		free(obj->attrs);
	free(obj);
}

bool	append_obj(t_scene *scene, t_obj *obj)
{
	t_obj	*objs;
	int	i;

	obj->id = scene->objs_count;
	objs = malloc(sizeof(t_obj) * (scene->objs_count + 1));
	if (!objs)
		return (false);
	i = 0;
	while (i < scene->objs_count)
	{
		objs[i] = scene->objs[i];
		objs[i].attrs = scene->objs[i].attrs;
		i++;
	}
	objs[i] = *obj;
	objs[i].attrs = obj->attrs;
	free(scene->objs);
	scene->objs = objs;
	scene->objs_count++;
	return (true);
}


t_scene	*load_scene(char *file_name)
{
	t_scene	*scene;
	char	*line;
	int		fd;

	if (!is_valid_name(file_name))
		return (NULL);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (NULL);
	scene = ft_calloc(sizeof(t_scene), 1);
	if (!scene)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		skip_spaces(&line);
		if (*line || *line != '\n')
		{
			if (ft_strncmp(line, "A ", 2) == 0)
			{
				if (!parse_ambient(line, scene))
					return (NULL);
			}
			else if (ft_strncmp(line, "C ", 2) == 0)
			{
				if (!parse_camera(line, scene))
					return (NULL);
			}
			else if (ft_strncmp(line, "L ", 2) == 0)
			{
				if (!parse_light(line, scene))
					return (NULL);
			}
			else
			{
				if (!parse_obj(line, scene))
					return (NULL);
			}
		}
		free(line);
		line = get_next_line(fd);
	}
	return (scene);
}
