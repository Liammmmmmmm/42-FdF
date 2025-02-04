/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_slope.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:02:27 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/04 15:02:40 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
