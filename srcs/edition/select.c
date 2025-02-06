/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:24:04 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/06 14:27:24 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	mouse_up_select(t_env *env)
{
	int		count_points;
	size_t	point_amount;
	size_t	i;
	int		start_x = env->points_selection.start_mouse_x;
	int		start_y = env->points_selection.start_mouse_y;
	int		stop_x = env->mouse_last_x;
	int		stop_y = env->mouse_last_y;
	int		tmp;

	env->selected_point.x = -1;
	env->selected_point.y = -1;
	if (start_x > stop_x)
	{
		tmp = stop_x;
		stop_x = start_x;
		start_x = tmp;
	}
	if (start_y > stop_y)
	{
		tmp = stop_y;
		stop_y = start_y;
		start_y = tmp;
	}
	point_amount = env->map->height * env->map->length;
	if (env->painter.is_active == 0)
	{
		count_points = 0;
		i = 0;
		while (i < point_amount)
		{
			if (env->point_list[i].x >= start_x && env->point_list[i].x <= stop_x
				&& env->point_list[i].y >= start_y && env->point_list[i].y <= stop_y)
			{
				if ((i % env->map->length) % env->points_reduction_factor == 0
					&& (i / env->map->length) % env->points_reduction_factor == 0)
					count_points++;
			}
			i++;	
		}
		env->points_selection.selected_points = malloc(sizeof(t_point) * count_points);
		if (!env->points_selection.selected_points)
			return ;
		env->points_selection.amount_of_points = count_points;
		env->points_selection.is_active = 1;
		i = 0;
		count_points = 0;
		while (i < point_amount)
		{
			if (env->point_list[i].x >= start_x && env->point_list[i].x <= stop_x
				&& env->point_list[i].y >= start_y && env->point_list[i].y <= stop_y)
			{
				if ((i % env->map->length) % env->points_reduction_factor == 0
					&& (i / env->map->length) % env->points_reduction_factor == 0)
				{
					env->points_selection.selected_points[count_points].x = i % env->map->length;
					env->points_selection.selected_points[count_points].y = i / env->map->length;
					count_points++;
				}
			}
			i++;	
		}
	}
	else
	{
		i = 0;
		while (i < point_amount)
		{
			if (env->point_list[i].x >= start_x && env->point_list[i].x <= stop_x
				&& env->point_list[i].y >= start_y && env->point_list[i].y <= stop_y)
			{
				if ((i % env->map->length) % env->points_reduction_factor == 0
					&& (i / env->map->length) % env->points_reduction_factor == 0)
					env->map->color_map[i / env->map->length][i % env->map->length] = env->painter.color;
			}
			i++;	
		}
	}
}
