/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_procedural.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 22:10:56 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/10 12:57:22 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_default_perlin(t_perlin_noise	*perlin)
{
	perlin->seed = 0;
	perlin->width = 256;
	perlin->height = 256;
	perlin->min = -100;
	perlin->max = 255;
	perlin->x_offset = 0;
	perlin->y_offset = 0;
	perlin->scale = 32.0f;
	perlin->octaves = 8;
	perlin->persistence = 0.5f;
	perlin->frequency = 1.0f;
	perlin->gradientX = NULL;
	perlin->gradientY = NULL;
	perlin->noise = NULL;
	perlin->heightmap = NULL;
	perlin->vector_grid_size_x = 0;
	perlin->vector_grid_size_y = 0;
}

int	save_one_line(t_map *map, t_perlin_noise *perlin, int i)
{
	int	x;

	map->map[i] = malloc(sizeof(int) * map->length);
	map->color_map[i] = malloc(sizeof(int) * map->length);
	if (!map->map[i])
		return (ft_free_tab_int(map->map, i + 1), ft_free_tab_int(map->color_map, i + 1), 0);
	x = 0;
	while (x < map->length)
	{
		map->map[i][x] = perlin->heightmap[i * map->length + x];
		map->color_map[i][x] = 0xffffff;
		x++;
	}
	return (1);
}

int	save_to_map(t_map *map, t_perlin_noise *perlin)
{
	int	i;

	map->height = perlin->height;
	map->length = perlin->width;
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
		if (save_one_line(map, perlin, i) == 0)
			return (free(map->edited), 0);
		i++;
	}
	return (1);
}

t_map	*procedural_map(t_env *env, int argc, char **argv)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (print_error("malloc failed"), NULL);
	init_default_perlin(&env->procedural.perlin_noise);
	if (argc == 2)
		print_info("You can add more parameters to the procedural generation :\n       ./fdf procedural [map_width] [map_height] [seed]");
	if (argc >= 3)
		env->procedural.perlin_noise.width = ft_atoui(argv[2]);
	if (argc >= 4)
		env->procedural.perlin_noise.height = ft_atoui(argv[3]);
	if (env->procedural.perlin_noise.width == 0 || env->procedural.perlin_noise.height == 0)
		return (free(map), print_error("invalid map size"), NULL);
	if (argc >= 5)
		env->procedural.perlin_noise.seed = ft_atoui(argv[4]);

	if (generate_perlin_noise(&env->procedural.perlin_noise) == 0)
		return (NULL);
	save_to_map(map, &env->procedural.perlin_noise);
	return (map);
}
