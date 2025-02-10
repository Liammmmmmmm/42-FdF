/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   biomes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:44:12 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/10 16:12:04 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_biome get_biome(int temperature, int humidity, int biome_height)
{
	if (biome_height <= 50) // Océans
	{
		if (temperature < 20) return FROZEN_OCEAN;  // Océan gelé (très froid)
		if (temperature < 50) return COLD_OCEAN;    // Océan froid
		return WARM_OCEAN;                         // Océan chaud
	}
	else if (biome_height <= 75) // Plaines
	{
		if (temperature < 30) return SNOWY_PLAIN;   // Plaine enneigée (froid)
		if (temperature > 70 && humidity < 30) return DESERT;  // Désert (chaud et sec)
		if (humidity > 70) return FOREST;          // Forêt (humide)
		return TEMPERED_PLAIN;                     // Plaine tempérée (cas général)
	}
	else // Montagnes (biome_height > 75)
	{
		if (temperature < 30) return COLD_MOUNTAIN;
		if (temperature > 70 && humidity < 30) return WARM_MOUNTAIN;
		return TEMPERED_MOUNTAIN;
	}
}



/*
	// Océans
	if (temperature <= 25) {
		if (humidity < 50) return FROZEN_OCEAN;  // Océan gelé (très froid)
		return MOUNTAIN;                      // Océan froid
	}
	if (temperature >= 70) {
		if (humidity < 30) return DESERT;       // Désert (très chaud et sec)
		return WARM_OCEAN;                      // Océan chaud
	}

	if (humidity > 75)
		return TEMPERED_OCEAN;

	// Montagnes
	if (temperature < 40) return COLD_OCEAN;    // Montagnes froides (altitude et température basses)

	// Plaines tempérées ou enneigées
	if (temperature < 50) {
		if (humidity < 40) return SNOWY_PLAIN;  // Plaine neigeuse (froid et sec)
		return TEMPERED_PLAIN;                  // Plaine tempérée (tempéré et sec)
	}

	// Forêts
	if (humidity > 60) return FOREST;          // Région humide → forêt

	// Plaines tempérées ou semi-arides
	if (humidity < 30) return TEMPERED_PLAIN;  // Climat sec mais pas désertique

	return TEMPERED_PLAIN;                     // Plaine tempérée (pour le reste des cas)

*/