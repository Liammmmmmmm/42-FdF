/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_buttons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:00:24 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/06 16:55:51 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	init_color_button(t_env *env, int i, int color)
{
	env->color_buttons[i].background_color = color;
	env->color_buttons[i].border_color = 0xffffff;
	env->color_buttons[i].height = 20;
	env->color_buttons[i].width = 30;
	env->color_buttons[i].x = 1880;
	env->color_buttons[i].y = 100 + 30 * i;
	env->color_buttons[i].param = malloc(sizeof(t_brush_c));
	if (!env->color_buttons[i].param)
		return (0); // AJOUTER GESTION ERREUR
	((t_brush_c *)env->color_buttons[i].param)->color = color;
	((t_brush_c *)env->color_buttons[i].param)->env = env;
	env->color_buttons[i].action = &change_brush_color;
	return (1);
}

int	init_buttons(t_env *env)
{
	int	i;
	int colors[16] = {
        0xFF0000, // Red
        0x00FF00, // Green
        0x0000FF, // Blue
        0xFFFF00, // Yellow
        0xFF00FF, // Magenta
        0x00FFFF, // Cyan
        0x800000, // Maroon
        0x808000, // Olive
        0x008000, // Dark Green
        0x800080, // Purple
        0x008080, // Teal
        0x000080, // Navy
        0xFFA500, // Orange
        0xA52A2A, // Brown
        0x8A2BE2, // Blue Violet
        0x5F9EA0  // Cadet Blue
    };

	i = 0;
	while (i < 16)
	{
		if(init_color_button(env, i, colors[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	init_slider(t_env *env)
{
	env->brush_size_slider.x = 1750;
	env->brush_size_slider.y = 70;
	env->brush_size_slider.height = 3;
	env->brush_size_slider.width = 150;
	env->brush_size_slider.bar_color = 0xffffff;
	env->brush_size_slider.min = 5;
	env->brush_size_slider.max = 200;
	env->brush_size_slider.point_color = 0x1193d9;
	env->brush_size_slider.value = &env->painter.radius;
}
