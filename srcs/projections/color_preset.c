/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_preset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:26:43 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/15 19:08:04 by lilefebv         ###   ########lyon.fr   */
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
	return (0xFFFFFF);
}
