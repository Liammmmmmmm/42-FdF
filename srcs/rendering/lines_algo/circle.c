/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:00:08 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/06 16:53:28 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_circle(int xc, int yc, int x, int y, t_env *env, int color)
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

void	circle_bres(int xc, int yc, int r, t_env *env, int color)
{
	int x = 0, y = r;
	int d = 3 - 2 * r;
	draw_circle(xc, yc, x, y, env, color);
	while (y >= x)
	{
		if (d > 0) {
			y--; 
			d = d + 4 * (x - y) + 10;
		}
		else
			d = d + 4 * x + 6;
		x++;
		draw_circle(xc, yc, x, y, env, color);
    }
}

void	draw_circle_comp(int xc, int yc, int x, int y, t_img *img, int color)
{
	put_pixel_image(img->img_str, xc + x, yc + y, color);
	put_pixel_image(img->img_str, xc - x, yc + y, color);
	put_pixel_image(img->img_str, xc + x, yc - y, color);
	put_pixel_image(img->img_str, xc - x, yc - y, color);
	put_pixel_image(img->img_str, xc + y, yc + x, color);
	put_pixel_image(img->img_str, xc - y, yc + x, color);
	put_pixel_image(img->img_str, xc + y, yc - x, color);
	put_pixel_image(img->img_str, xc - y, yc - x, color);
}

void	circle_bres_comp(int xc, int yc, int r, t_img *img, int color)
{
	int x = 0, y = r;
	int d = 3 - 2 * r;
	draw_circle_comp(xc, yc, x, y, img, color);
	while (y >= x)
	{
		if (d > 0) {
			y--; 
			d = d + 4 * (x - y) + 10;
		}
		else
			d = d + 4 * x + 6;
		x++;
		draw_circle_comp(xc, yc, x, y, img, color);
    }
}

void	draw_filled_circle(int xc, int yc, int r, t_img *img, int color)
{
	int	y;
	int	x;

	y = -r;
	while (y <= r)
	{
		x = -r;
		while (x <= r)
		{
			if (x * x + y * y <= r * r)
				put_pixel_image(img->img_str, xc + x, yc + y, color);
			x++;
		}
		y++;
	}
}
