/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:51:34 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/08 16:32:58 by lilefebv         ###   ########lyon.fr   */
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

void	render_frame(t_env *env)
{
	int y;

	y = 0;
	ft_bzero(env->img->img_str, WIN_WIDTH * WIN_HEIGHT * (env->img->bits / 8));
	calculate_every_projection(env);
	save_lines(env);
	if (Z_ORDERING)
		quicksort_lines(env->lines, 0, env->line_amount - 1);
	draw_every_lines(env);
	mlx_put_image_to_window(env->mlx, env->mlx_win, env->img->img, 0, 0);
	env->frames_gen += 1;
}
