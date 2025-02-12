/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procedural.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:39:10 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/12 10:49:28 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCEDURAL_H
# define PROCEDURAL_H

# include "structs.h"

t_biome			get_biome(int temperature, int humidity, int biome_height);

unsigned int	hash(int x, int y, unsigned int seed);
void			set_rivers(t_map *map);
void			generate_rivers(t_env *env, t_map *map);

#endif
