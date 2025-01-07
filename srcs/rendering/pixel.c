/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:59:26 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/07 17:09:11 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		calc_gradiant_color(t_point *point_a, t_point *point_b)
{
	unsigned char r;
	unsigned char g;
	unsigned char b;

	
}

void	put_pixel_image(char *str, int x, int y, int color)
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	int len;

	len = 1920;
	x += 1920 / 2;
	y += 1080 / 2;
	if (x < 0 || x >= len || y < 0 || y >= 1080)
		return;
	r = (color >> 16) & 0xff;
	g = (color >> 8) & 0xff;
	b = color & 0xff;
	str[(x * 4) + (len * 4 * y)] = b;
	str[(x * 4) + (len * 4 * y) + 1] = g;
	str[(x * 4) + (len * 4 * y) + 2] = r;
	str[(x * 4) + (len * 4 * y) + 3] = 0;
}