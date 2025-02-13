/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:53:59 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/13 12:11:56 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

unsigned int hash(int x, int y, unsigned int seed)
{
	unsigned int h;

	h = seed;
	h ^= x * 374761393U;
	h ^= y * 668265263U;
	h *= 3284157443U;
	h ^= h >> 13;
	h *= 1911520717U;
	h ^= h >> 16;
	return (h);
}

int	round_up_to_next_ten(int value)
{
	return ((value + 9) / 10) * 10;
}

float	lerp(float a, float b, float t)
{
	return a + t * (b - a);
}

void	free_perlin_map(t_perlin_map *perlin_map)
{
	clean_perlin(&perlin_map->perlin_noise);
	clean_perlin(&perlin_map->temperature);
	clean_perlin(&perlin_map->humidity);
	clean_perlin(&perlin_map->biome_height);
}
