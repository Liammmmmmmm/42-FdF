/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:24:26 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/08 12:04:29 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	is_point_in_frame(t_env *env, t_point *point)
{
	if (point->x < 0 || point->x >= env->win_width
		|| point->y < 0 || point->y >= env->win_height)
		return (0);
	return (1);
}
