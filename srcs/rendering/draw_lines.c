/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:08:34 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/04 17:32:04 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*thread_draw_lines(void *param)
{
	t_env	*env;
	int		y;

	env = ((t_thread_param *)param)->env;
	y = ((t_thread_param *)param)->start_ln - 1;
	while (++y < ((t_thread_param *)param)->end_ln)
	{
		if (env->line_algo == 0)
			draw_line(env->lines[y].start, env->lines[y].end, env);
		else if (env->line_algo == 1)
			draw_line_wu(env->lines[y].start, env->lines[y].end, env);
		else if (env->line_algo == 2)
			draw_line_bresenham(env->lines[y].start, env->lines[y].end, env);
	}
	return (NULL);
}

void	draw_every_lines(t_env *env)
{
	int	i;
	int	y;
	int	line_per_thread;

	line_per_thread = env->line_amount / env->proc_amount;
	i = 0;
	while (i < env->proc_amount)
	{
		env->threads_params[i].start_ln = i * line_per_thread;
		env->threads_params[i].end_ln = (i + 1) * line_per_thread;
		i++;
	}
	env->threads_params[i - 1].end_ln = env->line_amount;
	i = 0;
	while (i < env->proc_amount)
	{
		if (pthread_create(&env->threads[i], NULL, &thread_draw_lines, &env->threads_params[i]) != 0)
			break ;
		else
			y = env->threads_params[i].end_ln - 1;
		i++;
	}
	while (++y < env->line_amount)
	{
		if (env->line_algo == 0)
			draw_line(env->lines[y].start, env->lines[y].end, env);
		else if (env->line_algo == 1)
			draw_line_wu(env->lines[y].start, env->lines[y].end, env);
		else if (env->line_algo == 2)
			draw_line_bresenham(env->lines[y].start, env->lines[y].end, env);

	}
	while (i > 0)
	{
		pthread_join(env->threads[i - 1], NULL);
		i--;
	}
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
