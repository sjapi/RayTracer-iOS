/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 032zolotarev <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:57:20 by 032zolotarev      #+#    #+#             */
/*   Updated: 2025/07/15 18:41:46 by 032zolotarev     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROLS_H
# define CONTROLS_H

# include "minirt.h"
# include <stdbool.h>

/* key based funcs */
bool	handle_qweasd(int key, t_rt *info);
bool	handle_hjkl(int key, t_rt *info);
bool	handle_plus_minus(int key, t_rt *info);
bool	handle_xyz(int key, t_rt *info);
bool	handle_other_keys(int key, t_rt *info);

/* mode based funcs */
bool	translate_obj(t_obj *obj, int key);
bool	translate_cam(t_cam *cam, int key);
bool	rotate_obj(t_obj *obj, int key);
bool	rotate_cam(t_cam *cam, int key);

#endif
