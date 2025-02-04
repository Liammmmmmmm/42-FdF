/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:59:26 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/04 17:49:21 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	clamp_color(unsigned char color)
{
	if (color < 0)
		return (0);
	else if (color > 255)
		return (255);
	return (color);
}

int	calc_gradiant_color(int color_a, int color_b, double ratio)
{
	t_color	c_a;
	t_color	c_b;
	t_color	c_f;

	c_a.r = (color_a >> 16) & 0xff;
	c_a.g = (color_a >> 8) & 0xff;
	c_a.b = color_a & 0xff;
	c_b.r = (color_b >> 16) & 0xff;
	c_b.g = (color_b >> 8) & 0xff;
	c_b.b = color_b & 0xff;
	c_f.r = c_a.r + ratio * (c_b.r - c_a.r);
	c_f.g = c_a.g + ratio * (c_b.g - c_a.g);
	c_f.b = c_a.b + ratio * (c_b.b - c_a.b);
	c_f.r = clamp_color(c_f.r);
	c_f.g = clamp_color(c_f.g);
	c_f.b = clamp_color(c_f.b);
	return ((c_f.r << 16) | (c_f.g << 8) | c_f.b);
}

int	calc_gradiant_point(t_point *point_a, t_point *point_b, double ratio)
{
	return (calc_gradiant_color(point_a->color, point_b->color, ratio));
}

void	put_pixel_image(char *str, int x, int y, int color)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	int				len;

	len = WIN_WIDTH;
	if (x < 0 || x >= len || y < 0 || y >= WIN_HEIGHT)
		return ;
	r = (color >> 16) & 0xff;
	g = (color >> 8) & 0xff;
	b = color & 0xff;
	str[(x * 4) + (len * 4 * y)] = b;
	str[(x * 4) + (len * 4 * y) + 1] = g;
	str[(x * 4) + (len * 4 * y) + 2] = r;
	str[(x * 4) + (len * 4 * y) + 3] = 0;
}

void	put_pixel_z_ordered(t_env *env, int x, int y, int color, double depth)
{
	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
        return;
	if (env->protect_data_races)
		pthread_mutex_lock(&env->img->img_mutex);
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
	if (env->protect_data_races)
		pthread_mutex_unlock(&env->img->img_mutex);
}
