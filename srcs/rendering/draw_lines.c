/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:08:34 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/03 12:22:44 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel_z_ordered(t_env *env, int x, int y, int color, double depth)
{
	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
        return;
	if (env->z_ordering == 1)
	{
		if (env->img->img_depth[y * WIN_WIDTH + x] > depth)
		{
			put_pixel_image(env->img->img_str, x, y, color);
			env->img->img_depth[y * WIN_WIDTH + x] = depth;
		}
	}
	else
		put_pixel_image(env->img->img_str, x, y, color);
}

void	draw_line_x(t_point *point_a, t_point *point_b, t_env *env)
{
	float	m;
	int		dx;
	int		dy;
	int		temp;

	dx = point_b->x - point_a->x;
	dy = point_b->y - point_a->y;
	m = (float)dy / dx;
	if (point_b->x > point_a->x)
	{
		temp = point_a->x - 1;
		while (++temp <= point_b->x)
			put_pixel_z_ordered(env, temp, m * (temp - point_a->x) + point_a->y,
				calc_gradiant_point(point_a, point_b, (double)(temp - point_a->x) / dx),
				(point_a->z + point_b->z) / 2);
	}
	else
	{
		temp = point_b->x - 1;
		while (++temp <= point_a->x)
			put_pixel_z_ordered(env, temp, m * (temp - point_b->x) + point_b->y,
				calc_gradiant_point(point_a, point_b, (double)(temp - point_a->x) / dx),
				(point_a->z + point_b->z) / 2);
	}
}

void	draw_line_y(t_point *point_a, t_point *point_b, t_env *env)
{
	float	m;
	int		dx;
	int		dy;
	int		temp;

	dx = point_b->x - point_a->x;
	dy = point_b->y - point_a->y;
	m = (float)dx / dy;
	if (point_b->y > point_a->y)
	{
		temp = point_a->y - 1;
		while (++temp <= point_b->y)
			put_pixel_z_ordered(env, m * (temp - point_a->y) + point_a->x, temp,
				calc_gradiant_point(point_a, point_b, (double)(temp - point_a->y) / dy),
				(point_a->z + point_b->z) / 2);
	}
	else
	{
		temp = point_b->y - 1;
		while (++temp <= point_a->y)
			put_pixel_z_ordered(env, m * (temp - point_b->y) + point_b->x, temp,
				calc_gradiant_point(point_a, point_b, (double)(temp - point_a->y) / dy),
				(point_a->z + point_b->z) / 2);
	}
}

void	draw_line(t_point *point_a, t_point *point_b, t_env *env)
{
	int	dx;
	int	dy;

	dx = point_b->x - point_a->x;
	dy = point_b->y - point_a->y;
	if (abs(dy) <= abs(dx))
	{
		if (dx == 0)
			return ;
		draw_line_x(point_a, point_b, env);
	}
	else
	{
		if (dy == 0)
			return ;
		draw_line_y(point_a, point_b, env);
	}
}

void	draw_every_lines(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->line_amount)
		draw_line(env->lines[i].start, env->lines[i].end, env);
}

int	is_valid_line(t_env *env, t_point *point_a, t_point *point_b)
{
	int	one_point_in_frame;
	int	one_point_pos_z;

	one_point_in_frame
		= (is_point_in_frame(*point_a) || is_point_in_frame(*point_b));
	one_point_pos_z
		= (((*point_a).z > 0 && (*point_b).z > 0) || env->perspective == 2);
	if (!one_point_in_frame || !one_point_pos_z)
		return (0);
	return (1);
}
