/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:05:48 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/04 15:05:50 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line_bresenham(t_point *point_a, t_point *point_b, t_env *env)
{
	int x = point_a->x;
	int y = point_a->y;
	int odx = point_b->x - point_a->x;
	int ody = point_b->y - point_a->y;
	int dx = abs(odx);
	int dy = abs(ody);
	int sx = (point_a->x < point_b->x) ? 1 : -1;
	int sy = (point_a->y < point_b->y) ? 1 : -1;
	int err = dx - dy;
	int err2;

	double	depth = (point_a->z + point_b->z) / 2;
	double t;

	while (1)
	{
		t = (dx > dy) ? (double)(x - point_a->x) / odx : (double)(y - point_a->y) / ody;

		put_pixel_z_ordered(env, x, y, calc_gradiant_point(point_a, point_b, t), depth);
		if (x == point_b->x && y == point_b->y)
			break;

		err2 = 2 * err;
		if (err2 > -dy) { err -= dy; x += sx; }
		if (err2 < dx)  { err += dx; y += sy; }
	}
}
