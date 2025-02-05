/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:52:14 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/05 12:45:13 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_pixel_color(char *img_str, int x, int y)
{
	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return (0);
	
	int pixel_index = (y * WIN_WIDTH + x) * 4;
	return (img_str[pixel_index] & 0xFF) | 
			((img_str[pixel_index + 1] & 0xFF) << 8) | 
			((img_str[pixel_index + 2] & 0xFF) << 16);
}

void	put_pixel_alpha(t_env *env, int x, int y, int color, double alpha, double depth)
{
	int bg_color = get_pixel_color(env->img->img_str, x, y);
	int blended_color = calc_gradiant_color(bg_color, color, alpha);

	put_pixel_z_ordered(env, x, y, blended_color, depth);
}

void	draw_line_wu(t_point *point_a, t_point *point_b, t_env *env)
{
	double	x0 = point_a->x, y0 = point_a->y;
	double	x1 = point_b->x, y1 = point_b->y;
	int		c0 = point_a->color, c1 = point_b->color;
	int		steep = fabs(y1 - y0) > fabs(x1 - x0);
	double	temp;
	int		tempi;
	int		x;
	
	if (steep) // Transpose la ligne si elle est plus verticale qu'horizontale
	{
		temp = x0; x0 = y0; y0 = temp;
		temp = x1; x1 = y1; y1 = temp;
	}
	if (x0 > x1) // Assure que la ligne va de gauche à droite
	{
		temp = x0; x0 = x1; x1 = temp;
		temp = y0; y0 = y1; y1 = temp;
		
		tempi = c1; c1 = c0; c0 = tempi;
	}

	double dx = x1 - x0;
	double dy = y1 - y0;
	double gradient = (dx == 0) ? 1.0 : dy / dx;
	double xend, yend, xgap;
	int xpxl1, ypxl1, xpxl2, ypxl2;
	double	t;

	// Premier point
	xend = round(x0);
	yend = y0 + gradient * (xend - x0);
	xgap = 1.0 - (x0 + 0.5 - floor(x0 + 0.5));
	xpxl1 = (int)xend;
	ypxl1 = (int)yend;

	if (steep) // Premier pixel avec interpolation
	{
		put_pixel_alpha(env, ypxl1, xpxl1, point_b->color, (1.0 - (yend - floor(yend))) * xgap, point_a->z);
		put_pixel_alpha(env, ypxl1 + 1, xpxl1, point_b->color, (yend - floor(yend)) * xgap, point_a->z);
	}
	else
	{
		put_pixel_alpha(env, xpxl1, ypxl1, point_b->color, (1.0 - (yend - floor(yend))) * xgap, point_a->z);
		put_pixel_alpha(env, xpxl1, ypxl1 + 1, point_b->color, (yend - floor(yend)) * xgap, point_a->z);
	}

	double intery = yend + gradient; // Interpolation de y

	// Dernier point
	xend = round(x1);
	yend = y1 + gradient * (xend - x1);
	xgap = x1 + 0.5 - floor(x1 + 0.5);
	xpxl2 = (int)xend;
	ypxl2 = (int)yend;

	if (steep)
	{
		put_pixel_alpha(env, ypxl2, xpxl2, point_a->color, (1.0 - (yend - floor(yend))) * xgap, point_b->z);
		put_pixel_alpha(env, ypxl2 + 1, xpxl2, point_a->color, (yend - floor(yend)) * xgap, point_b->z);
	}
	else
	{
		put_pixel_alpha(env, xpxl2, ypxl2, point_a->color, (1.0 - (yend - floor(yend))) * xgap, point_b->z);
		put_pixel_alpha(env, xpxl2, ypxl2 + 1, point_a->color, (yend - floor(yend)) * xgap, point_b->z);
	}

	// Pixels principaux
	x = xpxl1 + 1;
	while (x < xpxl2)
	{
		if (steep)
		{
			t = (dy == 0) ? 1.0 : 1 - (yend - intery) / dy;
			
			put_pixel_alpha(env, (int)intery, x, calc_gradiant_color(c0, c1, t), (1.0 - (intery - floor(intery))), (point_a->z + point_b->z) / 2);
			put_pixel_alpha(env, (int)intery + 1, x, calc_gradiant_color(c0, c1, t), (intery - floor(intery)), (point_a->z + point_b->z) / 2);
		}
		else
		{
			t = (dy == 0) ? 1.0 : 1 - (yend - intery) / dy;
			
			put_pixel_alpha(env, x, (int)intery, calc_gradiant_color(c0, c1, t), (1.0 - (intery - floor(intery))), (point_a->z + point_b->z) / 2);
			put_pixel_alpha(env, x, (int)intery + 1, calc_gradiant_color(c0, c1, t), (intery - floor(intery)), (point_a->z + point_b->z) / 2);
		}
		intery += gradient;
		x++;
	}
}
