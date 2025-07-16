/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 032zolotarev <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 12:12:04 by 032zolotarev      #+#    #+#             */
/*   Updated: 2025/07/09 12:14:38 by 032zolotarev     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_color	int_to_color(int icolor)
{
	t_color	color;

	color.r = (icolor >> 16) & 0xff;
	color.g = (icolor >> 8) & 0xff;
	color.b = icolor & 0xff;
	return (color);
}

int	color_to_int(t_color color)
{
	return ((color.r & 0xFF) << 16) | ((color.g & 0xFF) << 8) | (color.b & 0xFF);
}
