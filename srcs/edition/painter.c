/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:25:42 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/06 14:32:03 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	paint_area(t_env *env)
{
	size_t	point_amount;
	size_t	i;

	if (env->painter.is_active == 0 || env->mouse_click_select == 0)
		return ;
	point_amount = env->map->height * env->map->length;
	i = 0;
	while (i < point_amount)
	{
		if (env->point_list[i].x >= env->mouse_last_x - env->painter.radius && env->point_list[i].x <= env->mouse_last_x + env->painter.radius
			&& env->point_list[i].y >= env->mouse_last_y - env->painter.radius && env->point_list[i].y <= env->mouse_last_y + env->painter.radius)
		{
			if ((i % env->map->length) % env->points_reduction_factor == 0
				&& (i / env->map->length) % env->points_reduction_factor == 0)
				env->map->color_map[i / env->map->length][i % env->map->length] = env->painter.color;
		}
		i++;	
	}
}
