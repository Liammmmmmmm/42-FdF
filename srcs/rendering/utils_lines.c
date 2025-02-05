/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:21:31 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/04 11:52:22 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	save_line(t_env *env, t_point *point_a, t_point *point_b, int i)
{
	env->lines[i].start = point_a;
	env->lines[i].end = point_b;
	env->lines[i].depth = (point_a->z + point_b->z) / 2;
}

static int ry(int y, t_env *env)
{
	if (y + env->points_reduction_factor >= env->map->height)
		return (y);
	return (y + env->points_reduction_factor);
}

static int rx(int x, t_env *env)
{
	if (x + env->points_reduction_factor >= env->map->length)
		return (x);
	return (x + env->points_reduction_factor);
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
		if (y % env->points_reduction_factor == 0)
		{
			x = -1;
			while (++x < env->map->length)
			{
				if (x % env->points_reduction_factor == 0)
				{
					if (x < env->map->length - 1 && is_valid_line(env,
							&env->point_list[y * env->map->length + x],
							&env->point_list[y * env->map->length + rx(x, env)]))
						save_line(env, &env->point_list[y * env->map->length + x],
							&env->point_list[y * env->map->length + rx(x, env)], i++);
					if (y < env->map->height - 1 && is_valid_line(env,
							&env->point_list[y * env->map->length + x],
							&env->point_list[ry(y, env) * env->map->length + x]))
						save_line(env, &env->point_list[y * env->map->length + x],
							&env->point_list[ry(y, env) * env->map->length + x], i++);
				}
			}
		}
	}
	env->line_amount = i;
}

