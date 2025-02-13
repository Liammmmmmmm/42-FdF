/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_buttons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:00:24 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/13 11:01:52 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	init_color_button(t_env *env, int i, int color)
{
	env->color_buttons[i].background_color = color;
	env->color_buttons[i].border_color = 0xffffff;
	env->color_buttons[i].background_color_on_click = color;
	env->color_buttons[i].border_color_on_click = 0x5c5c5c;
	env->color_buttons[i].height = 20;
	env->color_buttons[i].width = 30;
	env->color_buttons[i].x = 1880 - 40 * (i / 16);
	env->color_buttons[i].y = 100 + 30 * (i % 16);
	env->color_buttons[i].param = malloc(sizeof(t_brush_c));
	env->color_buttons[i].text = NULL;
	if (!env->color_buttons[i].param)
		return (0); // AJOUTER GESTION ERREUR
	((t_brush_c *)env->color_buttons[i].param)->color = color;
	((t_brush_c *)env->color_buttons[i].param)->env = env;
	env->color_buttons[i].action = &change_brush_color;
	return (1);
}

int	init_setmode_button(t_env *env, int i, char *text)
{
	i += 48;
	env->color_buttons[i].background_color = 0xaaa5b0;
	env->color_buttons[i].border_color = 0xffffff;
	env->color_buttons[i].background_color_on_click = 0xcac5d1;
	env->color_buttons[i].border_color_on_click = 0xe4dfeb;
	env->color_buttons[i].height = 20;
	env->color_buttons[i].width = 110;
	env->color_buttons[i].x = 1800;
	env->color_buttons[i].y = 580 + 30 * (i - 48);
	env->color_buttons[i].param = malloc(sizeof(t_brush_c));
	env->color_buttons[i].text = ft_strdup(text);
	if (!env->color_buttons[i].param || !env->color_buttons[i].text)
		return (0); // AJOUTER GESTION ERREUR
	((t_brush_c *)env->color_buttons[i].param)->color = i - 47;
	((t_brush_c *)env->color_buttons[i].param)->env = env;
	env->color_buttons[i].action = &change_brush_mode;
	return (1);
}

int	init_save_button(t_env *env, int i)
{
	env->color_buttons[i].background_color = 0xaaa5b0;
	env->color_buttons[i].border_color = 0xffffff;
	env->color_buttons[i].background_color_on_click = 0xcac5d1;
	env->color_buttons[i].border_color_on_click = 0xe4dfeb;
	env->color_buttons[i].height = 20;
	env->color_buttons[i].width = 150;
	env->color_buttons[i].x = 1750;
	env->color_buttons[i].y = 1040;
	env->color_buttons[i].param = malloc(sizeof(t_brush_c));
	env->color_buttons[i].text = ft_strdup("Save!");
	if (!env->color_buttons[i].param || !env->color_buttons[i].text)
		return (0); // AJOUTER GESTION ERREUR
	((t_brush_c *)env->color_buttons[i].param)->env = env;
	env->color_buttons[i].action = &save_map_button;
	return (1);
}

int	init_buttons(t_env *env)
{
	int	i;
	int colors[48] = {
        // Première colonne (Rouge à Jaune)
        0xFF0000, // Red
        0xFF4500, // Orange Red
        0xFF6347, // Tomato
        0xFF7F50, // Coral
        0xFFA500, // Orange
        0xFFD700, // Gold
        0xFFFF00, // Yellow
        0xFFFFE0, // Light Yellow
        0xFFFACD, // Lemon Chiffon
        0xFAFAD2, // Light Goldenrod Yellow
        0xFFE4B5, // Moccasin
        0xFFDAB9, // Peach Puff
        0xEEE8AA, // Pale Goldenrod
        0xF0E68C, // Khaki
        0xBDB76B, // Dark Khaki
        0xD3D3D3, // Light Grey

        // Deuxième colonne (Vert à Cyan)
        0x00FF00, // Green
        0x7FFF00, // Chartreuse
        0x7CFC00, // Lawn Green
        0xADFF2F, // Green Yellow
        0x9ACD32, // Yellow Green
	    0x32CD32, // Lime Green
        0x00FA9A, // Medium Spring Green
        0x00FF7F, // Spring Green
        0x3CB371, // Medium Sea Green
        0x2E8B57, // Sea Green
        0x20B2AA, // Light Sea Green
        0x66CDAA, // Medium Aquamarine
        0x8FBC8F, // Dark Sea Green
        0x90EE90, // Light Green
        0x98FB98, // Pale Green
        0xE0FFFF, // Light Cyan

        // Troisième colonne (Bleu à Violet + Gris/Noir/Blanc)
        0x0000FF, // Blue
        0x0000CD, // Medium Blue
        0x00008B, // Dark Blue
        0x000080, // Navy
        0x191970, // Midnight Blue
        0x4B0082, // Indigo
	    0x8A2BE2, // Blue Violet
        0x6A5ACD, // Slate Blue
        0x9370DB, // Medium Purple
        0x8B008B, // Dark Magenta
        0x9932CC, // Dark Orchid
        0xBA55D3, // Medium Orchid
        0xFFFFFF, // White
        0xA9A9A9, // Dark Grey
        0x696969, // Dim Grey
        0x000000  // Black
	};

	i = 0;
	while (i < 48)
	{
		if(init_color_button(env, i, colors[i]) == 0)
			return (0);
		i++;
	}
	init_setmode_button(env, 0, "UP");
	init_setmode_button(env, 1, "DOWN");
	init_setmode_button(env, 2, "FLATTERN");
	init_setmode_button(env, 3, "SMOOTH UP");
	init_setmode_button(env, 4, "SMOOTH DOWN");
	init_save_button(env, 53);
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
	env->brush_size_slider.is_clicked = 0;

	env->brush_intensity_slider.x = 1750;
	env->brush_intensity_slider.y = 40;
	env->brush_intensity_slider.height = 3;
	env->brush_intensity_slider.width = 150;
	env->brush_intensity_slider.bar_color = 0xffffff;
	env->brush_intensity_slider.min = 1;
	env->brush_intensity_slider.max = 100;
	env->brush_intensity_slider.point_color = 0x1193d9;
	env->brush_intensity_slider.value = &env->painter.intensity;
	env->brush_intensity_slider.is_clicked = 0;
}

void	init_text_input(t_env *env)
{
	env->save_input.background_color = 0xbfbfbf;
	env->save_input.border_color = 0xf0f0f0;
	env->save_input.border_color_focus = 0x1193d9;
	env->save_input.height = 20;
	env->save_input.width = 150;
	env->save_input.x = 1750;
	env->save_input.y = 1010;
	ft_strlcpy(env->save_input.placeholder, "File name", 256);
	env->save_input.max_char = 20;
	env->save_input.padding_left = 4;
	env->save_input.text_color = 0x0;
}
