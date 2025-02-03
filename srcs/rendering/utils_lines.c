/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:21:31 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/31 13:26:14 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	save_line(t_env *env, t_point *point_a, t_point *point_b, int i)
{
	env->lines[i].start = point_a;
	env->lines[i].end = point_b;
	env->lines[i].depth = (point_a->z + point_b->z) / 2;
}

void	save_lines(t_env *env)
{
	int	y;
	int	x;
	int	i;

	i = 0;
	y = -1;
	while (++y < env->map->height)
	{
		x = -1;
		while (++x < env->map->length)
		{
			if (x < env->map->length - 1 && is_valid_line(env,
					&env->point_list[y * env->map->length + x],
					&env->point_list[y * env->map->length + x + 1]))
				save_line(env, &env->point_list[y * env->map->length + x],
					&env->point_list[y * env->map->length + x + 1], i++);
			if (y < env->map->height - 1 && is_valid_line(env,
					&env->point_list[y * env->map->length + x],
					&env->point_list[(y + 1) * env->map->length + x]))
				save_line(env, &env->point_list[y * env->map->length + x],
					&env->point_list[(y + 1) * env->map->length + x], i++);
		}
	}
	env->line_amount = i;
}

