/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_point.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:22:04 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/10 17:23:55 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	save_point_at_mouse(t_env *env)
{
	size_t	point_amount;
	size_t	i;

	if (env->points_selection.is_active)
	{
		free(env->points_selection.selected_points);
		env->points_selection.is_active = 0;
	}
	if (env->is_control_down)
	{
		env->selected_point.x = -1;
		env->selected_point.y = -1;
		env->points_selection.start_mouse_x = env->mouse_last_x;
		env->points_selection.start_mouse_y = env->mouse_last_y;
	}
	else
	{
		if (env->painter.is_active == 0)
		{
			i = 0;
			point_amount = env->map->height * env->map->length;
			while (i < point_amount)
			{
				if (env->point_list[i].x >= env->mouse_last_x - SELECT_RANGE && env->point_list[i].x <= env->mouse_last_x + SELECT_RANGE
					&& env->point_list[i].y >= env->mouse_last_y - SELECT_RANGE && env->point_list[i].y <= env->mouse_last_y + SELECT_RANGE)
				{
					env->selected_point.x = i % env->map->length;
					env->selected_point.y = i / env->map->length;
					return ((void)ft_printf("Selected point : (%d, %d, %d), #%X\n", env->selected_point.x, env->selected_point.y, env->map->map[env->selected_point.y][env->selected_point.x], env->map->color_map[env->selected_point.y][env->selected_point.x]));
				}
				i++;	
			}

		}
		env->selected_point.x = -1;
		env->selected_point.y = -1;
	}
}

void	edit_point(int key, t_env *env)
{
	int	i;

	if (env->selected_point.x != -1)
	{
		if (key == KEY_B)
			env->map->map[env->selected_point.y][env->selected_point.x] -= 1;
		else if (key == KEY_N)
			env->map->map[env->selected_point.y][env->selected_point.x] += 1;
		else if (key == KEY_V)
			env->map->map[env->selected_point.y][env->selected_point.x] = 0;
	}
	else if (env->points_selection.is_active == 1)
	{
		i = 0;
		if (key == KEY_B)
		{
			while (i < env->points_selection.amount_of_points)
			{
				env->map->map[env->points_selection.selected_points[i].y][env->points_selection.selected_points[i].x] -= 1;
				i++;
			}
		}
		else if (key == KEY_N)
		{
			while (i < env->points_selection.amount_of_points)
			{
				env->map->map[env->points_selection.selected_points[i].y][env->points_selection.selected_points[i].x] += 1;
				i++;
			}
		}
		else if (key == KEY_V)
		{
			while (i < env->points_selection.amount_of_points)
			{
				env->map->map[env->points_selection.selected_points[i].y][env->points_selection.selected_points[i].x] = 0;
				i++;
			}
		}
	}
}
