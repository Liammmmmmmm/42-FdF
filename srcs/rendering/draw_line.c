/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:08:34 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/07 17:04:29 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_point *point_a, t_point *point_b, t_env *env)
{
	int	dx;
	int	dy;
	int	m;
	int temp;
	
	dx = point_b->x - point_a->x;
	dy = point_b->y - point_a->y;
	if (abs(dy) <= abs(dx))
	{
		m = dy / dx;
		if (point_b->x > point_a->x)
		{
			temp = point_a->x - 1;
			while (++temp <= point_b->x)
			{
				put_pixel_image(env->img->img_str, temp, m * (temp - point_a->x) + point_a->y, calc_gradiant_color());
			}
		}
		else
		{
			
		}
	}
}
