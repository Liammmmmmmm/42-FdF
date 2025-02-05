/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rectangle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:20:21 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/05 17:45:40 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_rectangle(t_env *env, int start_x, int start_y, int stop_x, int stop_y)
{
	int	i;
	int	tmp;

	if (start_x > stop_x)
	{
		tmp = stop_x;
		stop_x = start_x;
		start_x = tmp;
	}
	if (start_y > stop_y)
	{
		tmp = stop_y;
		stop_y = start_y;
		start_y = tmp;
	}
	i = start_x;
	while (i <= stop_x)
	{
		if (i % 5 == 0 || i % 5 == 1)
		{
			put_pixel_image(env->img->img_str, i, start_y, 0xFFFFFF);
			put_pixel_image(env->img->img_str, i, stop_y, 0xFFFFFF);
		}
		i++;
	}
	i = start_y;
	while (i <= stop_y)
	{
		if (i % 5 == 0 || i % 5 == 1)
		{
			put_pixel_image(env->img->img_str, start_x, i, 0xFFFFFF);
			put_pixel_image(env->img->img_str, stop_x, i, 0xFFFFFF);
		}
		i++;
	}
}
