/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_perlin_noise.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 22:08:13 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/10 12:46:55 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// idée de folie, des sliders centrés a 0 : comme les sliders sauf que y'a pas de
// limite de début ou fin. Imaginons je met le slider full a droite, ça va augmenter
// ma var de 100 et remettre le slider au centre, si je refait a droit ça refait 100 de plus
// comme ça je peux faire des sliders pour l'offset x et y de la map

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned int hash(int x, int y, unsigned int seed) {
	unsigned int h = seed;
	h ^= x * 374761393U;
	h ^= y * 668265263U;
	h *= 3284157443U;
	h ^= h >> 13;
	h *= 1911520717U;
	h ^= h >> 16;
	return h;
}

int	generate_vectors(t_perlin_noise *perlin)
{
	int		i;
	float	angle;

	perlin->vector_grid_division = 8;
	perlin->vector_grid_size_x = perlin->width / perlin->vector_grid_division + 1;
	perlin->vector_grid_size_y = perlin->height / perlin->vector_grid_division + 1;
	perlin->vector_grid_size_total = (perlin->vector_grid_size_x + 1) * (perlin->vector_grid_size_y + 1);
	perlin->gradientX = malloc(sizeof(float) * perlin->vector_grid_size_total);
	perlin->gradientY = malloc(sizeof(float) * perlin->vector_grid_size_total);
	if (!perlin->gradientX || !perlin->gradientY)
		return (free(perlin->gradientX), free(perlin->gradientY), 0);
	i = 0;
	while (i < perlin->vector_grid_size_total)
	{
		angle = (hash(i % (perlin->vector_grid_size_x + 1) + perlin->x_offset / perlin->vector_grid_division, i / (perlin->vector_grid_size_x + 1) + perlin->y_offset / perlin->vector_grid_division, perlin->seed) % 360) * (PI_10D / 180.0f);
		perlin->gradientX[i] = cos(angle);
		perlin->gradientY[i] = sin(angle);
		i++;
	}
	return (1);
}

float fade(float t)
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}

// Produit scalaire entre un gradient et le vecteur relatif
float dot_grid_gradient(t_perlin_noise *perlin, int ix, int iy, float x, float y)
{
    float dx = x - (float)ix;
    float dy = y - (float)iy;
	if (ix < 0 || iy < 0 || ix >= perlin->vector_grid_size_x || iy >= perlin->vector_grid_size_y)
        return 0.0f;
    return (dx * perlin->gradientX[iy * (perlin->vector_grid_size_x + 1) + ix] + dy * perlin->gradientY[iy * (perlin->vector_grid_size_x + 1) + ix]);
}

float perlin_noise(t_perlin_noise *perlin, float x, float y)
{
    int x0 = (int)floor(x);
    int x1 = x0 + 1;
    int y0 = (int)floor(y);
    int y1 = y0 + 1;

    float sx = fade(x - (float)x0);
    float sy = fade(y - (float)y0);

    float n0, n1, ix0, ix1;

    n0 = dot_grid_gradient(perlin, x0, y0, x, y);
    n1 = dot_grid_gradient(perlin, x1, y0, x, y);
    ix0 = (1.0f - sx) * n0 + sx * n1;

    n0 = dot_grid_gradient(perlin, x0, y1, x, y);
    n1 = dot_grid_gradient(perlin, x1, y1, x, y);
    ix1 = (1.0f - sx) * n0 + sx * n1;

    return ((1.0f - sy) * ix0 + sy * ix1);
}

float perlin_noise_multi(t_perlin_noise *perlin, float x, float y)
{
    float	total = 0;
    float	amplitude = 1.0f;
    float	max_value = 0;
	int		i;
	float	temp_frequency;

	temp_frequency = perlin->frequency;
	i = 0;
    while (i < perlin->octaves)
	{
        total += perlin_noise(perlin, x * temp_frequency, y * temp_frequency) * amplitude;
        max_value += amplitude;
        amplitude *= perlin->persistence;
        temp_frequency *= 2.0f;
		i++;
    }

    return total / max_value;
}

int		create_noise(t_perlin_noise *perlin)
{
	int		stop;
	int		i;

	stop = perlin->width * perlin->height;
	perlin->noise = malloc(sizeof(float) * stop);
	if (!perlin->noise)
		return (0);
	i = 0;
	while (i < stop)
	{
		perlin->noise[i] = perlin_noise_multi(perlin, (i % perlin->width + (perlin->x_offset % perlin->vector_grid_division)) / perlin->scale, (i / perlin->width + (perlin->y_offset % perlin->vector_grid_division)) / perlin->scale);
		if (perlin->noise[i] < perlin->min_val)
			perlin->min_val = perlin->noise[i];
		else if (perlin->noise[i] > perlin->max_val)
			perlin->max_val = perlin->noise[i];
		i++;
	}
	return (1);
}

void	normalize_heightmap(t_perlin_noise *perlin)
{
	int		i;
	int		stop;

	i = 0;
	stop = perlin->width * perlin->height;
	while (i < stop)
	{
		perlin->heightmap[i] = (perlin->max - perlin->min) * (perlin->noise[i] - perlin->min_val) / (perlin->max_val - perlin->min_val) + perlin->min;
		i++;
	}
}


void	debug_print_vectors(t_perlin_noise *perlin)
{
	int		i;

	printf("%d, %d, %d\n", perlin->vector_grid_size_x, perlin->vector_grid_size_y, perlin->vector_grid_size_total);

	i = 0;
	while (i < perlin->vector_grid_size_total)
	{
		if (i % (perlin->vector_grid_size_x + 1) == 0)
			printf("\n");
		printf("%d: (%f, %f) ", i, perlin->gradientX[i], perlin->gradientY[i]);
		i++;
	}
	printf("\n");
	printf("\n");
}

int	generate_perlin_noise(t_perlin_noise *perlin)
{
	srand(perlin->seed);
	if (generate_vectors(perlin) == 0)
		return (0);
	//debug_print_vectors(perlin);
	perlin->heightmap = malloc(sizeof(int) * perlin->width * perlin->height);
	if (!perlin->heightmap)
		return (free(perlin->gradientX), free(perlin->gradientY), 0);
	perlin->min_val = 1e6;
	perlin->max_val = -1e6;
	if (create_noise(perlin) == 0)
		return (free(perlin->gradientX), free(perlin->gradientY), free(perlin->heightmap), 0);
	normalize_heightmap(perlin);
	return (1);
}

void print_heightmap2(t_perlin_noise *perlin) {
    const char levels[] = " .:-=+*#%@";
    int num_levels = sizeof(levels) - 1;

    for (unsigned int y = 0; y < perlin->height; y += 2) {
        for (unsigned int x = 0; x < perlin->width; x += 1) {
            int val = perlin->heightmap[perlin->width * y + x];
            char c = levels[(val * num_levels) / 256];
            printf("%c", c);
        }
        printf("\n");
    }
}

void	clean_perlin(t_perlin_noise *perlin)
{
	free(perlin->gradientX);
	free(perlin->gradientY);
	free(perlin->noise);
	free(perlin->heightmap);
}

// int main() {
// 	t_perlin_noise	perlin;

// 	perlin.seed = 42;
// 	perlin.width = 256;
// 	perlin.height = 256;
// 	perlin.min = 0;
// 	perlin.max = 255;
// 	perlin.x_offset = 0;
// 	perlin.y_offset = 0;
// 	perlin.scale = 16.0f;
// 	perlin.octaves = 8;
// 	perlin.persistence = 0.5f;
// 	perlin.frequency = 1.0f;
// 	perlin.gradientX = NULL;
// 	perlin.gradientY = NULL;
// 	perlin.noise = NULL;
// 	perlin.heightmap = NULL;
// 	perlin.vector_grid_size_x = 0;
// 	perlin.vector_grid_size_y = 0;

// 	generate_perlin_noise(&perlin);
// 	print_heightmap2(&perlin);

// 	clean_perlin(&perlin);
//     return 0;
// }
