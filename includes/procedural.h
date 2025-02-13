/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procedural.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:39:10 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/13 12:12:03 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCEDURAL_H
# define PROCEDURAL_H

# include "structs.h"

t_biome			get_biome(int temperature, int humidity, int biome_height);

unsigned int	hash(int x, int y, unsigned int seed);
void			set_rivers(t_map *map);
void			generate_rivers(t_env *env, t_map *map);
int				round_up_to_next_ten(int value);
float			lerp(float a, float b, float t);
float			apply_biome_modification(float base_height, t_biome biome, int x, int y);
float			get_final_height(float perlin_value, t_map *map, t_perlin_map *perlin_map, float blend_factor, int x, int y);
int				get_point_color(float base_height, int actual_height, t_biome biome, int x, int y, t_perlin_map *perlin_map);
void			free_perlin_map(t_perlin_map *perlin_map);

#endif
