/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_procedural.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 22:10:56 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/10 16:11:05 by lilefebv         ###   ########lyon.fr   */
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
	perlin->min = 000;
	perlin->max = 255;
	perlin->x_offset = 0;
	perlin->y_offset = 0;
	perlin->scale = 128.0f;
	perlin->octaves = 4;
	perlin->persistence = 1.2f;
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
	perlin->persistence = 0.5f;
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

int	save_one_line(t_map *map, t_perlin_map *perlin_map, int i)
{
	int	x;

	map->map[i] = malloc(sizeof(int) * map->length);
	map->color_map[i] = malloc(sizeof(int) * map->length);
	if (!map->map[i])
		return (ft_free_tab_int(map->map, i + 1), ft_free_tab_int(map->color_map, i + 1), 0);
	x = 0;
	while (x < map->length)
	{
		//map->map[i][x] = perlin->heightmap[i * map->length + x];
		map->map[i][x] = 0;
		t_biome biome = get_biome(perlin_map->temperature.heightmap[i * map->length + x], perlin_map->biome_height.heightmap[i * map->length + x], perlin_map->humidity.heightmap[i * map->length + x]);
		int color;
		if (biome == FROZEN_OCEAN)
			color = 0xD0F1FF;
		else if (biome == COLD_OCEAN)
			color = 0x3335D1;
		else if (biome == TEMPERED_OCEAN)
			color = 0x3372D1;
		else if (biome == WARM_OCEAN)
			color = 0x00C8FF;
		else if (biome == TEMPERED_PLAIN)
			color = 0x7BDD6F;
		else if (biome == SNOWY_PLAIN)
			color = 0xD9F5D6;
		else if (biome == DESERT)
			color = 0xEEEE86;
		else if (biome == FOREST)
			color = 0x2CB55A;
		else if (biome == COLD_MOUNTAIN)
			color = 0xF1FBFF;
		else if (biome == TEMPERED_MOUNTAIN)
			color = 0x888C8D;
		else if (biome == WARM_MOUNTAIN)
			color = 0xEBC958;
		else
			color = 0x0;

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
	map->edited = malloc(sizeof(char) * map->height * map->length);
	if (!map->map || !map->color_map || !map->edited)
		return (free(map->map), free(map->color_map), free(map->edited), 0);
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
