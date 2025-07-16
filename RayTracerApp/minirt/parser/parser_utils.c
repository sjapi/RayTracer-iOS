/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:03:20 by haaghaja          #+#    #+#             */
/*   Updated: 2025/07/15 21:43:00 by 032zolotarev     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "utils.h"
#include "parser.h"

bool	is_valid_name(char *file_name)
{
	int	size;

	size = ft_strlen(file_name);
	if (size < 3)
		return (false);
	if (ft_strcmp(&file_name[size - 3], ".rt") != 0)
		return (false);
	return (true);
}

bool	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

bool	is_float(char *num)
{
	while (*num >= '0' && *num <= '9')
		num++;
	if (*num == '.' && num[1] >= '0' && num[1] <= '9')
	{
		num++;
		while (*num >= '0' && *num <= '9')
			num++;
	}
	if (*num && *num != '\n' && !is_whitespace(*num))
		return (false);
	return (true);
}

bool	is_int(char *num)
{
	int	digits;

	digits = 0;
	while (*num >= '0' && *num <= '9')
	{
		digits++;
		num++;
	}
	if ((*num && *num != '\n' && !is_whitespace(*num)) || digits > 10)
		return (false);
	return (true);
}

bool	is_correct_color(char *str)
{
	int	commas;
	int	digits;

	commas = 0;
	skip_spaces(&str);
	while (*str)
	{
		if (skip_integer(&str, &digits) == 0 || digits > 3)
			return (false);
		if (!*str || *str == '\n' || is_whitespace(*str))
			break ;
		if (*str == ',')
			commas++;
		else if (!is_whitespace(*str))
			return (false);
		str++;
	}
	return (commas == 2);
}

bool	is_correct_coordinate(char *str)
{
	int	commas;
	int	digits;

	commas = 0;
	skip_spaces(&str);
	while (str)
	{
		if (!parse_float(&str, &digits))
			return (false);
		if (!*str || *str == '\n' || is_whitespace(*str))
			break ;
		if (*str == ',')
		{
			commas++;
			str++;
		}
		else if (*str < 0 && *str > 9)
			return (false);
	}
	return (commas == 2);
}

bool	is_checkerboard(char *str)
{
	if (ft_strncmp("checkerboard", str, 12) != 0)
		return (false);
	if (str[12] && str[12] != '\n' && !is_whitespace(str[12]))
		return (false);
	return (true);	
}

bool	is_mirror(char *str)
{
	if (ft_strncmp("mirror", str, 6) != 0)
		return (false);
	if (str[6] && str[6] != '\n' && !is_whitespace(str[6]))
		return (false);
	return (true);	
}

// ================================================

void	skip_spaces(char **str)
{
	while (is_whitespace(**str))
		(*str)++;
}

bool	skip_integer(char **str, int *digits)
{
	*digits = 0;
	while (**str >= '0' && **str <= '9')
	{
		(*digits)++;
		(*str)++;
	}
	return (*digits > 0);
}

void	next_info(char **str)
{
	while (**str && !is_whitespace(**str))
		(*str)++;
	skip_spaces(str);
}

// ===============================================
bool	parse_float(char **str, int *digits)
{
	*digits = 0;
	if (**str == '-')
		(*str)++;
	while (**str >= '0' && **str <= '9')
	{
		(*digits)++;
		(*str)++;
	}
	if (!**str || **str == '\n' || is_whitespace(**str) || **str == ',')
		return (*digits > 0);
	if (**str != '.' || *digits == 0)
		return (false);
	(*str)++;
	*digits = 0;
	while (**str >= '0' && **str <= '9')
	{
		(*digits)++;
		(*str)++;
	}
	return (*digits > 0);
}
