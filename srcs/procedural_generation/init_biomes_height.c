/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_biomes_height.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:04:39 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/13 12:09:05 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	dune_height(int x)
{
	int t = x % 25;

	switch (t)
	{
		case 0: return (2);
		case 1: return (2);
		case 2: return (2);
		case 3: return (2);
		case 4: return (3);
		case 5: return (3);
		case 6: return (3);
		case 7: return (4);
		case 8: return (4);
		case 9: return (4);
		case 10: return (4);
		case 11: return (5);
		case 12: return (5);
		case 13: return (5);
		case 14: return (5);
		case 15: return (5);
		case 16: return (3);
		case 17: return (1);
		case 18: return (0);
		case 19: return (0);
		case 20: return (0);
		case 21: return (0);
		case 22: return (1);
		case 23: return (1);
		case 24: return (1);
	}
	return (0);
}

float	apply_biome_modification(float base_height, t_biome biome, int x, int y)
{
	switch (biome)
	{
		case FROZEN_OCEAN:
			return 62;
		case COLD_OCEAN:
		case TEMPERED_OCEAN:
		case WARM_OCEAN:
			return base_height > 30 ? 36 + (base_height / 60) * 32 : 36 + (base_height / 60) * 32 + (base_height - 30) * 0.7;

		case TEMPERED_PLAIN:
		{
			if (hash(x, y, base_height) % 200 == 0)
				return base_height * 0.4f + 75 * 0.6f + 1;
			else if (hash(x, y, base_height) % 2 == 0)
			{
				if (hash(x - 1, y, base_height) % 200 == 0)
					return base_height * 0.4f + 75 * 0.6f + 1;
				if (hash(x, y - 1, base_height) % 200 == 0)
					return base_height * 0.4f + 75 * 0.6f + 1;
			}
			return base_height * 0.4f + 75 * 0.6f;
		}
		case SNOWY_PLAIN:
			return base_height * 0.4f + 75 * 0.6f + 1;
		case DESERT:
			return base_height * 0.4f + 75 * 0.6f + dune_height(x + sqrt(y * y + x * x));

		case FOREST:
			return base_height * 0.4f + 75 * 0.6f + fabs(2 * sinf((float)hash(x, y, base_height))) + 2;

		case COLD_MOUNTAIN:
			return ((base_height * 0.4f + 75 * 0.6f) - 75) * 2 + base_height + 4;
		case TEMPERED_MOUNTAIN:
			return ((base_height * 0.4f + 75 * 0.6f) - 75) * 2 + base_height + fabs(sinf((float)hash(x, y, base_height))) + 2;
		case WARM_MOUNTAIN:
			return round_up_to_next_ten(((base_height * 0.4f + 75 * 0.6f) - 75) * 2 + base_height) + ((int)(((base_height * 0.4f + 75 * 0.6f) - 75) * 2 + base_height) % 10) / 4 - 4;

		default:
			return base_height;
	}
}

float	get_final_height(float perlin_value, t_map *map, t_perlin_map *perlin_map, float blend_factor, int x, int y)
{
	float base_height = perlin_value;
	t_biome biome = perlin_map->biome_map[y * map->length + x];
	t_biome bxp1 = biome;
	if (x + 1 < map->length) 
		bxp1 = get_biome(
			perlin_map->temperature.heightmap[y * map->length + x + 1],
			perlin_map->humidity.heightmap[y * map->length + x + 1],
			perlin_map->biome_height.heightmap[y * map->length + x + 1]
		);
	t_biome byp1 = biome;
	if (y + 1 < map->height) 
		byp1 = get_biome(
			perlin_map->temperature.heightmap[(y + 1) * map->length + x],
			perlin_map->humidity.heightmap[(y + 1) * map->length + x],
			perlin_map->biome_height.heightmap[(y + 1) * map->length + x]
		);
	
	float height_a = apply_biome_modification(base_height, biome, x, y);
	float height_b = apply_biome_modification(base_height, bxp1, x, y);
	float height_c = apply_biome_modification(base_height, byp1, x, y);

	if (fabs(height_a - height_b) > fabs(height_a - height_c))
		return lerp(height_a, height_b, blend_factor);
	else
		return lerp(height_a, height_c, blend_factor);
}
