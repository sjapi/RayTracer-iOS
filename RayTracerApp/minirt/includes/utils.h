/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:23:26 by azolotar          #+#    #+#             */
/*   Updated: 2025/07/15 19:21:24 by 032zolotarev     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minirt.h"
# include <stdbool.h>
# include <stdio.h>

typedef struct	s_color
{
	int	r;
	int g;
	int	b;
}	t_color;

/* libft */
int		    ft_strlen(char *str);
int		    ft_strcmp(const char *s1, const char *s2);
int		    ft_strncmp(const char *s1, const char *s2, int n);
int		    ft_atoi(char *str);
float	    ft_atof(char *str);
void	    *ft_memcpy(void *dest, const void *src, size_t n);
void	    *ft_bzero(void *s, size_t n);
void	    *ft_calloc(size_t count, size_t size);
int		    ft_abs(int n);

/* miniRT related */
int	        get_amb_color(t_amb_light *amb);

/* vectors */
bool	    v_normalized(t_vec3 p);
t_vec3	    v_add(t_vec3 a, t_vec3 b);
t_vec3	    v_scale(t_vec3 v, float s);
t_vec3	    v_cross(t_vec3 a, t_vec3 b);
t_vec3	    v_normalize(t_vec3 v);
t_vec3	    v_sub(t_vec3 a, t_vec3 b);
float		v_dot(t_vec3 a, t_vec3 b);
float		v_len(t_vec3 v);

/* colors */
t_color		int_to_color(int icolor);
int			color_to_int(t_color color);

/* other */
int			clamp(int val, int min, int max);
float		clampf(float val, float min, float max);

float	    get_nx(int x, float aspect_ratio, float tan_fov, float width);
float	    get_ny(int y, float aspect_ratio, float height);

#endif
