/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_biomes_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:04:59 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/13 12:10:26 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	color_by_biome_only(const t_biome biome)
{
	int color;

	switch (biome)
	{
		case FROZEN_OCEAN: color = 0xD0F1FF; break;
		case COLD_OCEAN: color = 0x3335D1; break;
		case TEMPERED_OCEAN: color = 0x3372D1; break;
		case WARM_OCEAN: color = 0x00C8FF; break;
		case TEMPERED_PLAIN: color = 0x7BDD6F; break;
		case SNOWY_PLAIN: color = 0xD9F5D6; break;
		case DESERT: color = 0xEEEE86; break;
		case FOREST: color = 0x2CB55A; break;
		case COLD_MOUNTAIN: color = 0xF1FBFF; break;
		case TEMPERED_MOUNTAIN: color = 0x888C8D; break;
		case WARM_MOUNTAIN: color = 0xEBC958; break;
		default: color = 0x0;
	}
	return (color);
}

int	dune_color(int x)
{
	int t = x % 25;

	switch (t)
	{
		case 15: return (0xbab488);
		case 16: return (0xbab488);
		case 17: return (0xbab488);
		case 18: return (0xbab488);
	}
	return (0xd7d09b);
}

int get_ocean_color(int x, int y, int linelength, int ylength, t_biome *biome_map)
{
    t_biome current_biome = biome_map[y * linelength + x];

    int base_color;
    if (current_biome == COLD_OCEAN)
        base_color = 0x3335D1;
    else if (current_biome == TEMPERED_OCEAN)
        base_color = 0x3372D1;
    else if (current_biome == WARM_OCEAN)
        base_color = 0x00C8FF;
    else
        return 0;

    int closest_dist = 6;
    int target_color = base_color;

    for (int dy = -5; dy <= 5; dy++)
	{
        for (int dx = -5; dx <= 5; dx++)
		{
            int nx = x + dx;
            int ny = y + dy;

            if (nx < 0 || ny < 0 || nx >= linelength || ny >= ylength)
                continue ;

            t_biome neighbor_biome = biome_map[ny * linelength + nx];

            if (neighbor_biome != current_biome && (neighbor_biome == COLD_OCEAN || neighbor_biome == TEMPERED_OCEAN || neighbor_biome == WARM_OCEAN))
            {
                int neighbor_color;
                if (neighbor_biome == COLD_OCEAN)
                    neighbor_color = 0x3335D1;
                else if (neighbor_biome == TEMPERED_OCEAN)
                    neighbor_color = 0x3372D1;
                else
                    neighbor_color = 0x00C8FF;

                int dist = abs(dx) + abs(dy);
                if (dist < closest_dist)
				{
                    closest_dist = dist;
                    target_color = neighbor_color;
                }
            }
        }
    }

    if (closest_dist <= 5)
        return calc_gradiant_color(base_color, target_color, (5.0 - closest_dist) / 10.0);

    return base_color;
}


int	get_point_color(float base_height, int actual_height, t_biome biome, int x, int y, t_perlin_map *perlin_map)
{
	if (perlin_map->color_by_biome_only)
		return (color_by_biome_only(biome));
	(void)base_height;
	switch (biome)
	{
		case FROZEN_OCEAN:
			return 0xD0F1FF;
		case COLD_OCEAN:
			return get_ocean_color(x, y, perlin_map->temperature.width, perlin_map->temperature.height, perlin_map->biome_map);
		case TEMPERED_OCEAN:
			return get_ocean_color(x, y, perlin_map->temperature.width, perlin_map->temperature.height, perlin_map->biome_map);
		case WARM_OCEAN:
			return get_ocean_color(x, y, perlin_map->temperature.width, perlin_map->temperature.height, perlin_map->biome_map);
		case TEMPERED_PLAIN:
		{
			if (perlin_map->humidity.heightmap[y * perlin_map->humidity.width + x] > 40 && perlin_map->temperature.heightmap[y * perlin_map->temperature.width + x] < 50)
			{
				t_uint hashv = hash(x, y, perlin_map->perlin_noise.seed) % 70;
				if (hashv == 0)
					return (0xde4028);
				if (hashv == 1)
					return (0xd47aeb);
			}
			if (hash(x, y, base_height) % 200 == 0)
				return (0x888C8D);
			else if (hash(x, y, base_height) % 2 == 0)
			{
				if (hash(x - 1, y, base_height) % 200 == 0)
					return (0x888C8D);
				if (hash(x, y - 1, base_height) % 200 == 0)
					return (0x888C8D);
			}
			if (hash(x, y, base_height) % 3)
				return (0x63c768);
			return (0x7BDD6F);
		}
		case SNOWY_PLAIN:
		{
			t_uint hashv = hash(x, y, perlin_map->perlin_noise.seed) % 3;
			if (hashv == 0)
				return (0xcdebca);
			if (hashv == 1)
				return (0xdcedda);
			return (0xD9F5D6);
		}
		case DESERT:
			return dune_color(x + sqrt(y * y + x * x));
		case FOREST: 
		{
			t_uint hashv = hash(x, y, perlin_map->perlin_noise.seed) % 4;
			if (hashv == 0)
				return (0x249e4d);
			if (hashv == 1)
				return (0x28944c);
			if (hashv == 2)
				return (0x33b05d);
			return (0x2CB55A);
		}
		case COLD_MOUNTAIN:
			return 0xF1FBFF;
		case TEMPERED_MOUNTAIN:
		{
			t_uint hashv = hash(x, y, perlin_map->perlin_noise.seed) % 4;
			if (hashv == 0)
				return (0x717475);
			if (hashv == 1)
				return (0x828a8c);
			if (hashv == 2)
				return (0x959a9c);
			return 0x888C8D;
		}
		case WARM_MOUNTAIN:
		{
			if (actual_height <= 80)
				return (0xbb6520);
			if (actual_height == 87)
				return (0x412920);
			if (actual_height == 97 || actual_height == 98)
				return (0x722f24);
			if (actual_height == 107)
				return (0xa28b7c);
			if (actual_height == 108)
				return (0x412920);
			return 0x774935;
		}
		default:
			return 0x0;
	}
}
