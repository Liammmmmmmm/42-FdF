/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:08:34 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/04 15:09:58 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_every_lines(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->line_amount)
		if (env->line_algo == 0)
			draw_line(env->lines[i].start, env->lines[i].end, env);
		else if (env->line_algo == 1)
			draw_line_wu(env->lines[i].start, env->lines[i].end, env);
		else if (env->line_algo == 2)
			draw_line_bresenham(env->lines[i].start, env->lines[i].end, env);
}

int	is_valid_line(t_env *env, t_point *point_a, t_point *point_b)
{
	int	one_point_in_frame;
	int	one_point_pos_z;

	if (point_a == point_b)
		return (0);
	one_point_in_frame = (is_point_in_frame(*point_a) || is_point_in_frame(*point_b));
	one_point_pos_z = (((*point_a).z > 0 && (*point_b).z > 0) || env->perspective == 2);
	if (!one_point_in_frame || !one_point_pos_z)
		return (0);
	return (1);
}
