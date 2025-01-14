/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:21:31 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/14 14:40:09 by lilefebv         ###   ########lyon.fr   */
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

void	swap_lines(t_line *a, t_line *b)
{
	t_line	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	partition(t_line *lines, int low, int high, int order)
{
	float	pivot;
	int		i;
	int		j;

	pivot = lines[high].depth;
	i = (low - 1);
	j = low;
	while (j < high)
	{
		if (lines[j].depth > pivot && order == 0)
		{
			i++;
			swap_lines(&lines[i], &lines[j]);
		}
		if (lines[j].depth < pivot && order == 1)
		{
			i++;
			swap_lines(&lines[i], &lines[j]);
		}
		j++;
	}
	swap_lines(&lines[i + 1], &lines[high]);
	return (i + 1);
}

void	quicksort_lines(t_line *lines, int low, int high, int order)
{
	int	pi;

	if (low < high)
	{
		pi = partition(lines, low, high, order);
		quicksort_lines(lines, low, pi - 1, order);
		quicksort_lines(lines, pi + 1, high, order);
	}
}
