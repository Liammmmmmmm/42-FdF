/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_procedural.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 22:10:56 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/11 13:30:39 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	init_default_perlin(t_perlin_noise *perlin, t_uint width, t_uint height, t_uint seed)
{
	perlin->seed = seed;
	perlin->width = width;
	perlin->height = height;
	perlin->min = -10;
	perlin->max = 10;
	perlin->x_offset = 0;
	perlin->y_offset = 0;
	perlin->scale = 128.0f;
	perlin->octaves = 4;
	perlin->persistence = 0.5f;
	perlin->frequency = 1.0f;
	perlin->gradientX = NULL;
	perlin->gradientY = NULL;
	perlin->noise = NULL;
	perlin->heightmap = NULL;
	perlin->vector_grid_size_x = 0;
	perlin->vector_grid_size_y = 0;
}

void	init_temperature_perlin(t_perlin_noise *perlin, t_uint width, t_uint height, t_uint seed)
{
	perlin->seed = seed + 1;
	perlin->width = width;
	perlin->height = height;
	perlin->min = 0;
	perlin->max = 100;
	perlin->x_offset = 0;
	perlin->y_offset = 0;
	perlin->scale = 128.0f;
	perlin->octaves = 4;
	perlin->persistence = 0.1f;
	perlin->frequency = 1.0f;
	perlin->gradientX = NULL;
	perlin->gradientY = NULL;
	perlin->noise = NULL;
	perlin->heightmap = NULL;
	perlin->vector_grid_size_x = 0;
	perlin->vector_grid_size_y = 0;
}

void	init_humidity_perlin(t_perlin_noise *perlin, t_uint width, t_uint height, t_uint seed)
{
	perlin->seed = seed + 2;
	perlin->width = width;
	perlin->height = height;
	perlin->min = 0;
	perlin->max = 100;
	perlin->x_offset = 0;
	perlin->y_offset = 0;
	perlin->scale = 128.0f;
	perlin->octaves = 4;
	perlin->persistence = 0.5f;
	perlin->frequency = 1.0f;
	perlin->gradientX = NULL;
	perlin->gradientY = NULL;
	perlin->noise = NULL;
	perlin->heightmap = NULL;
	perlin->vector_grid_size_x = 0;
	perlin->vector_grid_size_y = 0;
}

void	init_height_perlin(t_perlin_noise *perlin, t_uint width, t_uint height, t_uint seed)
{
	perlin->seed = seed + 3;
	perlin->width = width;
	perlin->height = height;
	perlin->min = 0;
	perlin->max = 100;
	perlin->x_offset = 0;
	perlin->y_offset = 0;
	perlin->scale = 128.0f;
	perlin->octaves = 4;
	perlin->persistence = 0.2f;
	perlin->frequency = 1.0f;
	perlin->gradientX = NULL;
	perlin->gradientY = NULL;
	perlin->noise = NULL;
	perlin->heightmap = NULL;
	perlin->vector_grid_size_x = 0;
	perlin->vector_grid_size_y = 0;
}

float lerp(float a, float b, float t)
{
    return a + t * (b - a);
}

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

int round_up_to_next_ten(int value)
{
    return ((value + 9) / 10) * 10;
}

float apply_biome_modification(float base_height, t_biome biome, int x, int y)
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
			return base_height * 0.4f + 75 * 0.6f;
		case SNOWY_PLAIN:
			return base_height * 0.4f + 75 * 0.6f + 1;
		case DESERT:
			return base_height * 0.4f + 75 * 0.6f + dune_height(x + sqrt(y * y + x * x));

		case FOREST:
			return base_height * 0.4f + 75 * 0.6f + fabs(2 * sinf((float)hash(x, y, base_height))) + 2;

		case COLD_MOUNTAIN:
			return ((base_height * 0.4f + 75 * 0.6f) - 75) * 2 + base_height + 2;
		case TEMPERED_MOUNTAIN:
			return ((base_height * 0.4f + 75 * 0.6f) - 75) * 2 + base_height + fabs(sinf((float)hash(x, y, base_height)));
		case WARM_MOUNTAIN:
			return round_up_to_next_ten(((base_height * 0.4f + 75 * 0.6f) - 75) * 2 + base_height) + ((int)(((base_height * 0.4f + 75 * 0.6f) - 75) * 2 + base_height) % 10) / 4 - 4;

		default:
			return base_height;
	}
}

float get_final_height(float perlin_value, t_map *map, t_perlin_map *perlin_map, float blend_factor, int x, int y)
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


int	save_one_line(t_map *map, t_perlin_map *perlin_map, int i)
{
	int	x;

	map->map[i] = malloc(sizeof(int) * map->length);
	map->color_map[i] = malloc(sizeof(int) * map->length);
	if (!map->map[i] || !map->color_map[i])
		return (ft_free_tab_int(map->map, i + 1), ft_free_tab_int(map->color_map, i + 1), 0);
	
	x = 0;
	while (x < map->length)
	{
		t_biome biome = perlin_map->biome_map[i * map->length + x];

		float blend_factor = 0.5f;
		
		float perlin_value = perlin_map->perlin_noise.heightmap[i * map->length + x] + perlin_map->biome_height.heightmap[i * map->length + x];
		map->map[i][x] = get_final_height(perlin_value, map, perlin_map, blend_factor, x, i);

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
		map->color_map[i][x] = color;
		x++;
	}
	return (1);
}

int	save_to_map(t_map *map, t_perlin_map *perlin_map)
{
	int	i;

	map->height = perlin_map->perlin_noise.height;
	map->length = perlin_map->perlin_noise.width;
	map->have_color = 1;
	map->highest = -2147483648;

	map->map = malloc(sizeof(int *) * map->height);
	map->color_map = malloc(sizeof(int *) * map->height);
	perlin_map->biome_map = malloc(sizeof(t_biome) * map->height * map->length);
	map->edited = malloc(sizeof(char) * map->height * map->length);
	if (!map->map || !map->color_map || !perlin_map->biome_map || !map->edited)
		return (free(map->map), free(map->color_map), free(perlin_map->biome_map), free(map->edited), 0);
	
	i = map->height * map->length;
	while (i > 0)
	{
		i--;
		perlin_map->biome_map[i] = get_biome(perlin_map->temperature.heightmap[i], perlin_map->humidity.heightmap[i], perlin_map->biome_height.heightmap[i]);
	}

	i = 0;
	while (i < map->height)
	{
		if (save_one_line(map, perlin_map, i) == 0)
			return (free(map->edited), 0);
		i++;
	}
	return (1);
}


int	setup_perlins(t_env *env, int argc, char **argv)
{
	t_uint	width;
	t_uint	height;
	t_uint	seed;
	
	width = 256;
	height = 256;
	seed = 0;
	if (argc == 2)
		print_info("You can add more parameters to the procedural generation :\n       ./fdf procedural [map_width] [map_height] [seed]");
	if (argc >= 3)
		width = ft_atoui(argv[2]);
	if (argc >= 4)
		height = ft_atoui(argv[3]);
	if (width == 0 || height == 0)
		return (print_error("invalid map size"), 0);
	if (argc >= 5)
		seed = ft_atoui(argv[4]);

	init_default_perlin(&env->procedural.perlin_noise, width, height, seed);
	init_temperature_perlin(&env->procedural.temperature, width, height, seed);
	init_humidity_perlin(&env->procedural.humidity, width, height, seed);
	init_height_perlin(&env->procedural.biome_height, width, height, seed);
	return (1);
}

void	free_perlin_map(t_perlin_map *perlin_map)
{
	clean_perlin(&perlin_map->perlin_noise);
	clean_perlin(&perlin_map->temperature);
	clean_perlin(&perlin_map->humidity);
	clean_perlin(&perlin_map->biome_height);
}

t_map	*procedural_map(t_env *env, int argc, char **argv)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (print_error("malloc failed"), NULL);
	if (setup_perlins(env, argc, argv) == 0)
		return (free(map), NULL);

	if (generate_perlin_noise(&env->procedural.perlin_noise) == 0)
		return (NULL);
	if (generate_perlin_noise(&env->procedural.temperature) == 0)
		return (free_perlin_map(&env->procedural), NULL);
	if (generate_perlin_noise(&env->procedural.humidity) == 0)
		return (free_perlin_map(&env->procedural), NULL);
	if (generate_perlin_noise(&env->procedural.biome_height) == 0)
		return (free_perlin_map(&env->procedural), NULL);
	save_to_map(map, &env->procedural);
	return (map);
}
