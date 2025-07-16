/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 22:14:00 by haaghaja          #+#    #+#             */
/*   Updated: 2025/07/11 22:20:06 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include "utils.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	l;

	if (size == 0 || count == 0)
	{
		ptr = malloc(1);
		ft_bzero(ptr, 1);
		return (ptr);
	}
	if (size == SIZE_MAX / count)
		return (NULL);
	l = size * count;
	ptr = malloc(l);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, l);
	return (ptr);
}
