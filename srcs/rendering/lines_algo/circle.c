/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:00:08 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/05 15:07:53 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	drawCircle(int xc, int yc, int x, int y, t_env *env, int color)
{
	put_pixel_image(env->img->img_str, xc + x, yc + y, color);
	put_pixel_image(env->img->img_str, xc - x, yc + y, color);
	put_pixel_image(env->img->img_str, xc + x, yc - y, color);
	put_pixel_image(env->img->img_str, xc - x, yc - y, color);
	put_pixel_image(env->img->img_str, xc + y, yc + x, color);
	put_pixel_image(env->img->img_str, xc - y, yc + x, color);
	put_pixel_image(env->img->img_str, xc + y, yc - x, color);
	put_pixel_image(env->img->img_str, xc - y, yc - x, color);
}

void	circleBres(int xc, int yc, int r, t_env *env, int color)
{
	int x = 0, y = r;
	int d = 3 - 2 * r;
	drawCircle(xc, yc, x, y, env, color);
	while (y >= x)
	{
		if (d > 0) {
			y--; 
			d = d + 4 * (x - y) + 10;
		}
		else
			d = d + 4 * x + 6;
		x++;
		drawCircle(xc, yc, x, y, env, color);
    }
}
