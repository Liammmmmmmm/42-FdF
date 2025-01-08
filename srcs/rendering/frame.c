/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:51:34 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/08 12:12:35 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	calculate_every_projection(t_env *env)
{
	int	y;
	int	x;

	y = -1;
	while (++y < env->map->height)
	{
		x = -1;
		while (++x < env->map->length)
		{
			calculate_point_projection(x, y, env);
			put_pixel_image(env->img->img_str, env->point_list[y * env->map->length + x]->x, env->point_list[y * env->map->length + x]->y, 0x00FF00);
		}
	}
}

void	draw_every_lines(t_env *env)
{
	int	y;
	int	x;

	y = -1;
	while (++y < env->map->height)
	{
		x = -1;
		while (++x < env->map->length)
		{
			if (x < env->map->length - 1 && (is_point_in_frame(env, env->point_list[y * env->map->length + x]) || is_point_in_frame(env, env->point_list[y * env->map->length + x + 1])))
				draw_line(env->point_list[y * env->map->length + x], env->point_list[y * env->map->length + x + 1], env);
			if (y < env->map->height - 1 && (is_point_in_frame(env, env->point_list[y * env->map->length + x]) || is_point_in_frame(env, env->point_list[(y + 1) * env->map->length + x])))
				draw_line(env->point_list[y * env->map->length + x], env->point_list[(y + 1) * env->map->length + x], env);
		}
	}
}

void	render_frame(t_env *env)
{
	int y;

	y = 0;
	// if (env == NULL || env->img == NULL || env->img->img_str == NULL)
	// 	return;
	ft_bzero(env->img->img_str, env->win_width * env->win_height * (env->img->bits / 8));
	calculate_every_projection(env);
	draw_every_lines(env);
	mlx_put_image_to_window(env->mlx, env->mlx_win, env->img->img, 0, 0);
	env->frames_gen += 1;
}
