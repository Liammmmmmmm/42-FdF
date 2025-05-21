/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:59:26 by lilefebv          #+#    #+#             */
/*   Updated: 2025/05/21 10:19:26 by lilefebv         ###   ########lyon.fr   */
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

inline int	calc_gradiant_color(int color_a, int color_b, double ratio)
{
	return ((clamp_color(((color_a >> 16) & 0xff) + ratio * (((color_b >> 16) & 0xff) - ((color_a >> 16) & 0xff))) << 16)
	| (clamp_color(((color_a >> 8) & 0xff) + ratio * (((color_b >> 8) & 0xff) - ((color_a >> 8) & 0xff))) << 8)
	| clamp_color((color_a & 0xff) + ratio * ((color_b & 0xff) - (color_a & 0xff))));
}

int	calc_gradiant_point(t_point *point_a, t_point *point_b, double ratio)
{
	return (calc_gradiant_color(point_a->color, point_b->color, ratio));
}

inline void	put_pixel_image(char *str, int x, int y, int color)
{
	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	((int *)str + x + (WIN_WIDTH * y))[0] = color;
}

void	put_pixel_z_ordered(t_env *env, int x, int y, int color, double depth)
{
	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
        return;
	// if (env->protect_data_races)
	// 	pthread_mutex_lock(&env->img->img_mutex);
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
	// if (env->protect_data_races)
	// 	pthread_mutex_unlock(&env->img->img_mutex);
}
