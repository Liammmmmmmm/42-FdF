/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_point.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:22:04 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/06 11:50:42 by lilefebv         ###   ########lyon.fr   */
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
		i = 0;
		point_amount = env->map->height * env->map->length;
		while (i < point_amount)
		{
			if (env->point_list[i].x >= env->mouse_last_x - SELECT_RANGE && env->point_list[i].x <= env->mouse_last_x + SELECT_RANGE
				&& env->point_list[i].y >= env->mouse_last_y - SELECT_RANGE && env->point_list[i].y <= env->mouse_last_y + SELECT_RANGE)
			{
				env->selected_point.x = i % env->map->length;
				env->selected_point.y = i / env->map->length;
				return ;
			}
			i++;	
		}
		env->selected_point.x = -1;
		env->selected_point.y = -1;
	}
}

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
	count_points = 0;
	i = 0;
	point_amount = env->map->height * env->map->length;
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
