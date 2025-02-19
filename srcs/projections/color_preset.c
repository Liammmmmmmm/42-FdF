/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_preset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:26:43 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/11 15:08:37 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	color_preset1(int z)
{
	if (z < -600)
		return (0x000080);
	if (z < -450)
		return (calc_gradiant_color(0x284A9E, 0x000080, (z + 600) / 150.0));
	if (z < -250)
		return (calc_gradiant_color(0x000080, 0x4682B4, (z + 500) / 200.0));
	if (z < 0)
		return (calc_gradiant_color(0x4682B4, 0x00BFFF, (z + 250) / 250.0));
	if (z < 7)
		return (calc_gradiant_color(0x00BFFF, 0xFFF44F, (z) / 7.0));
	if (z < 50)
		return (calc_gradiant_color(0xFFF44F, 0x98FB98, (z - 7) / 43.0));
	if (z < 150)
		return (calc_gradiant_color(0x98FB98, 0x228B22, (z - 50) / 100.0));
	if (z < 300)
		return (calc_gradiant_color(0x228B22, 0x574A27, (z - 150) / 150.0));
	if (z < 550)
		return (calc_gradiant_color(0x574A27, 0xFFFFFF, (z - 300) / 250.0));
	return (0xFFFFFF);
}

static int	color_preset2(int z)
{
	if (z < -500)
		return (0x000080);
	if (z < -200)
		return (0x4682B4);
	if (z < 0)
		return (0x00BFFF);
	if (z < 10)
		return (0xFFF44F);
	if (z < 50)
		return (0x98FB98);
	if (z < 200)
		return (0x228B22);
	if (z < 350)
		return (0x574A27);
	if (z < 800)
		return (0xFFFFFF);
	return (0xFFFFFF);
}

static int	color_preset3(int z)
{
	if (z < -500)
		return (0x2B2B2B);
	if (z < -200)
		return (calc_gradiant_color(0x2B2B2B, 0x4A4A4A, (z + 500) / 300.0));
	if (z < 0)
		return (calc_gradiant_color(0x4A4A4A, 0x6E6E6E, (z + 200) / 200.0));
	if (z < 100)
		return (calc_gradiant_color(0x6E6E6E, 0xA9A9A9, z / 100.0));
	if (z < 300)
		return (calc_gradiant_color(0xA9A9A9, 0xC2B280, (z - 100) / 200.0));
	if (z < 500)
		return (calc_gradiant_color(0xC2B280, 0xEDEDED, (z - 300) / 200.0));
	return (0xFFFFFF);
}

int	color_preset_procedural(int z)
{
	if (z < 30)
		return (0x000060);
	if (z < 62)
		return (calc_gradiant_color(0x000060, 0x1E90FF, (z - 30) / 32.0));
	if (z < 70)
		return (calc_gradiant_color(0x1E90FF, 0xC2B280, (z - 62) / 8.0));
	if (z < 100)
		return (calc_gradiant_color(0xC2B280, 0x228B22, (z - 70) / 30.0));
	if (z < 140)
		return (calc_gradiant_color(0x228B22, 0x888C8D, (z - 100) / 40.0));
	if (z < 180)
		return (calc_gradiant_color(0x888C8D, 0xA9A9A9, (z - 140) / 40.0));
	return (0xFFFFFF);
}

int	get_color_by_preset(t_env *env, int x, int y)
{
	int	z;

	z = env->map->map[y][x];
	if (env->color_preset == 0)
		return (calc_gradiant_color(COLOR_MIN, COLOR_MAX,
				(double)env->map->map[y][x] / env->map->highest));
	else if (env->color_preset == 1)
		return (color_preset1(z));
	else if (env->color_preset == 2)
		return (color_preset2(z));
	else if (env->color_preset == 3)
		return (color_preset3(z));
	else if (env->color_preset == 4)
		return (color_preset_procedural(z));
	return (0xFFFFFF);
}
