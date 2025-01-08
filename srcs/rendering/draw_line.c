/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:08:34 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/08 12:34:14 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_point *point_a, t_point *point_b, t_env *env)
{
	int	dx;
	int	dy;
	float	m;
	int temp;

	dx = point_b->x - point_a->x;
	dy = point_b->y - point_a->y;
	if (abs(dy) <= abs(dx))
	{
		if (dx == 0)
			return ;
		m = (float)dy / dx;
		if (point_b->x > point_a->x)
		{
			temp = point_a->x - 1;
			while (++temp <= point_b->x)
				put_pixel_image(env->img->img_str, temp, m * (temp - point_a->x) + point_a->y, calc_gradiant_color(point_a, point_b, (double)(temp - point_a->x) / dx));
		}
		else
		{
			temp = point_b->x - 1;
			while (++temp <= point_a->x)
				put_pixel_image(env->img->img_str, temp, m * (temp - point_b->x) + point_b->y, calc_gradiant_color(point_b, point_a, (1 - (double)(temp - point_b->x) / dx)));
		}
	}
	else
	{
		if (dy == 0)
			return ;
		m = (float)dx / dy;
		if (point_b->y > point_a->y)
		{
			temp = point_a->y - 1;
			while (++temp <= point_b->y)
				put_pixel_image(env->img->img_str, m * (temp - point_a->y) + point_a->x, temp, calc_gradiant_color(point_a, point_b, (double)(temp - point_a->y) / dy));
		}
		else
		{
			temp = point_b->y - 1;
			while (++temp <= point_a->y)
				put_pixel_image(env->img->img_str, m * (temp - point_b->y) + point_b->x, temp, calc_gradiant_color(point_b, point_a, (1 - (double)(temp - point_b->y) / dy)));
		}
	}
}