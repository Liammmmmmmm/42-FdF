/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rivers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:20:48 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/12 13:01:26 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"



void	generate_river(t_map *map, int x, int y, int river_length)
{

	if (map->map[y][x] <= 62 || river_length > 1000)
		return ;
	
	map->rivers[y][x] = 1;

	int	xm1 = 0;
	int	xp1 = 0;
	int	ym1 = 0;
	int	yp1 = 0;

	if (x > 0)
		if (map->map[y][x] + 1 >= map->map[y][x - 1] && map->rivers[y][x - 1] == 0)
			xm1 = map->map[y][x] - map->map[y][x - 1] + 2;
	if (x < map->length - 1)
		if (map->map[y][x] + 1 >= map->map[y][x + 1] && map->rivers[y][x + 1] == 0)
			xp1 = map->map[y][x] - map->map[y][x + 1] + 2;
	if (y > 0)
		if (map->map[y][x] + 1 >= map->map[y - 1][x] && map->rivers[y - 1][x] == 0)
			ym1 = map->map[y][x] - map->map[y - 1][x] + 2;
	if (x < map->height - 1)
		if (map->map[y][x] + 1 >= map->map[y + 1][x] && map->rivers[y + 1][x] == 0)
			yp1 = map->map[y][x] - map->map[y + 1][x] + 2;

	if (xm1 == 0 && xp1 == 0 && ym1 == 0 && yp1 == 0)
		return ;

	int	biggest = xm1;
	if (xp1 > biggest)
		biggest = xp1;
	if (ym1 > biggest)
		biggest = ym1;
	if (yp1 > biggest)
		biggest = yp1;

	xm1 = xm1 == biggest ? 1 : 0;
	xp1 = xp1 == biggest ? 1 : 0;
	ym1 = ym1 == biggest ? 1 : 0;
	yp1 = yp1 == biggest ? 1 : 0;

	int total = xm1 + xp1 + ym1 + yp1;

	if (total == 0)
		return ;
		
	t_uint	hashv = hash(x, y, map->map[y][x]) % total;
	t_uint	i = 0;

	if (xm1)
	{
		if (i == hashv)
			return generate_river(map, x - 1, y, river_length + 1);
		i++;
	}
	if (xp1)
	{
		if (i == hashv)
			return generate_river(map, x + 1, y, river_length + 1);
		i++;
	}
	if (ym1)
	{
		if (i == hashv)
			return generate_river(map, x, y - 1, river_length + 1);
		i++;
	}
	if (yp1)
	{
		if (i == hashv)
			return generate_river(map, x, y + 1, river_length + 1);
		i++;
	}
}

void	generate_rivers(t_env *env, t_map *map)
{
	for (int y = 0; y < map->height; y++)
	{
		for (int x = 0; x < map->length; x++)
		{
			if (map->map[y][x] > 90)
			{
				if (hash(x, y, env->procedural.perlin_noise.seed) % 1000 < 2)
				{
					generate_river(map, x, y, 0);
				}
			}
		}
	}
}

void	set_rivers(t_map *map)
{
	for (int y = 0; y < map->height; y++)
	{
		for (int x = 0; x < map->length; x++)
		{
			if (map->rivers[y][x] == 1)
			{
				map->map[y][x] -= 1;
				map->color_map[y][x] = 0x3192d4;
			}
		}
	}
}
