/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_procedural.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 22:10:56 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/13 12:11:50 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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


int	save_one_line(t_map *map, t_perlin_map *perlin_map, int i)
{
	int	x;

	map->map[i] = malloc(sizeof(int) * map->length);
	map->color_map[i] = malloc(sizeof(int) * map->length);
	map->rivers[i] = malloc(sizeof(int) * map->length);
	if (!map->map[i] || !map->color_map[i])
		return (ft_free_tab_int(map->map, i + 1), ft_free_tab_int(map->rivers, i + 1), ft_free_tab_int(map->color_map, i + 1), 0);
	
	x = 0;
	while (x < map->length)
	{
		t_biome biome = perlin_map->biome_map[i * map->length + x];

		float blend_factor = 0.5f;
		
		float perlin_value = perlin_map->perlin_noise.heightmap[i * map->length + x] + perlin_map->biome_height.heightmap[i * map->length + x];
		map->map[i][x] = get_final_height(perlin_value, map, perlin_map, blend_factor, x, i);
		map->rivers[i][x] = 0;
		map->color_map[i][x] = get_point_color(perlin_value, map->map[i][x], biome, x, i, perlin_map);
		x++;
		
	}
	return (1);
}

int	save_to_map(t_env *env, t_map *map, t_perlin_map *perlin_map)
{
	int	i;

	map->height = perlin_map->perlin_noise.height;
	map->length = perlin_map->perlin_noise.width;
	map->have_color = 1;
	perlin_map->color_by_biome_only = 0;
	map->highest = -2147483648;

	map->map = malloc(sizeof(int *) * map->height);
	map->rivers = malloc(sizeof(int *) * map->height);
	map->color_map = malloc(sizeof(int *) * map->height);
	perlin_map->biome_map = malloc(sizeof(t_biome) * map->height * map->length);
	map->edited = malloc(sizeof(char) * map->height * map->length);
	if (!map->map || !map->color_map || !perlin_map->biome_map || !map->edited)
		return (free(map->map), free(map->rivers), free(map->color_map), free(perlin_map->biome_map), free(map->edited), 0);
	
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
	generate_rivers(env, map);
	set_rivers(map);
	ft_free_tab_int(map->rivers, map->height);
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
	save_to_map(env, map, &env->procedural);
	return (map);
}
