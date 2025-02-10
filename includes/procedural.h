/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procedural.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:39:10 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/10 16:06:19 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCEDURAL_H
# define PROCEDURAL_H

typedef enum e_biome
{
	FROZEN_OCEAN,
	COLD_OCEAN,
	TEMPERED_OCEAN,
	WARM_OCEAN,
	TEMPERED_PLAIN,
	SNOWY_PLAIN,
	DESERT,
	FOREST,
	COLD_MOUNTAIN,
	TEMPERED_MOUNTAIN,
	WARM_MOUNTAIN
}	t_biome;

t_biome	get_biome(int temperature, int humidity, int biome_height);

#endif
