/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:59:26 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/08 16:33:34 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		calc_gradiant_color(t_point *point_a, t_point *point_b, double ratio)
{
	t_color	c_a;
	t_color	c_b;
	t_color	c_f;

	c_a.r = (point_a->color >> 16) & 0xff;
	c_a.g = (point_a->color >> 8) & 0xff;
	c_a.b = point_a->color & 0xff;
	c_b.r = (point_b->color >> 16) & 0xff;
	c_b.g = (point_b->color >> 8) & 0xff;
	c_b.b = point_b->color & 0xff;
	c_f.r = c_a.r + ratio * (c_b.r - c_a.r);
	c_f.g = c_a.g + ratio * (c_b.g - c_a.g);
	c_f.b = c_a.b + ratio * (c_b.b - c_a.b);
	return ((c_f.r << 16) | (c_f.g << 8) | c_f.b);
}

void	put_pixel_image(char *str, int x, int y, int color)
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	int len;

	len = WIN_WIDTH;
	if (x < 0 || x >= len || y < 0 || y >= WIN_HEIGHT)
		return;
	r = (color >> 16) & 0xff;
	g = (color >> 8) & 0xff;
	b = color & 0xff;
	str[(x * 4) + (len * 4 * y)] = b;
	str[(x * 4) + (len * 4 * y) + 1] = g;
	str[(x * 4) + (len * 4 * y) + 2] = r;
	str[(x * 4) + (len * 4 * y) + 3] = 0;
}