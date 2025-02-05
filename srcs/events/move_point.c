/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_point.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:22:04 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/05 14:56:00 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	save_point_at_mouse(t_env *env)
{
	size_t	point_amount;
	size_t	i;

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

void	edit_point(int key, t_env *env)
{
	if (env->selected_point.x == -1)
		return ;
	if (key == KEY_B)
		env->map->map[env->selected_point.y][env->selected_point.x] -= 1;
	else if (key == KEY_N)
		env->map->map[env->selected_point.y][env->selected_point.x] += 1;
}
