/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_perlin_noise.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 22:08:13 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/08 23:56:25 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

//#include "fdf.h"

// idée de folie, des sliders centrés a 0 : comme les sliders sauf que y'a pas de
// limite de début ou fin. Imaginons je met le slider full a droite, ça va augmenter
// ma var de 100 et remettre le slider au centre, si je refait a droit ça refait 100 de plus
// comme ça je peux faire des sliders pour l'offset x et y de la map

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 256
#define HEIGHT 256
#define GRID_SIZE 16
#define SCALE 16.0f

#define OCTAVES 4
#define PERSISTENCE 0.5f

float gradientX[GRID_SIZE + 1][GRID_SIZE + 1];
float gradientY[GRID_SIZE + 1][GRID_SIZE + 1];

// Génère des gradients unitaires aléatoires
void generate_gradients() {
    for (int y = 0; y <= GRID_SIZE; y++) {
        for (int x = 0; x <= GRID_SIZE; x++) {
            float angle = ((float)rand() / RAND_MAX) * 2.0f * M_PI;
            gradientX[y][x] = cos(angle);
            gradientY[y][x] = sin(angle);
        }
    }
}

// Fonction fade de Perlin pour un meilleur lissage
float fade(float t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

// Produit scalaire entre un gradient et le vecteur relatif
float dot_grid_gradient(int ix, int iy, float x, float y) {
    float dx = x - (float)ix;
    float dy = y - (float)iy;
    return (dx * gradientX[iy][ix] + dy * gradientY[iy][ix]);
}

// Génération du bruit de Perlin 2D
float perlin_noise(float x, float y) {
    int x0 = (int)floor(x);
    int x1 = x0 + 1;
    int y0 = (int)floor(y);
    int y1 = y0 + 1;

    float sx = fade(x - (float)x0);
    float sy = fade(y - (float)y0);

    float n0, n1, ix0, ix1;

    n0 = dot_grid_gradient(x0, y0, x, y);
    n1 = dot_grid_gradient(x1, y0, x, y);
    ix0 = (1.0f - sx) * n0 + sx * n1;

    n0 = dot_grid_gradient(x0, y1, x, y);
    n1 = dot_grid_gradient(x1, y1, x, y);
    ix1 = (1.0f - sx) * n0 + sx * n1;

    return ((1.0f - sy) * ix0 + sy * ix1);
}

// Bruit de Perlin multi-octaves
float perlin_noise_multi(float x, float y) {
    float total = 0;
    float amplitude = 1.0f;
    float frequency = 0.3f;
    float max_value = 0;

    for (int i = 0; i < OCTAVES; i++) {
        total += perlin_noise(x * frequency, y * frequency) * amplitude;
        max_value += amplitude;
        amplitude *= PERSISTENCE;
        frequency *= 2.0f;
    }

    return total / max_value;
}

// Génère la heightmap en normalisant les valeurs entre 0 et 255
void generate_heightmap(unsigned char heightmap[WIDTH][HEIGHT], int x_offset, int y_offset) {
    float min_val = 1e6, max_val = -1e6;
    float noise[WIDTH][HEIGHT];

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            noise[y][x] = perlin_noise_multi((x + x_offset) / SCALE, (y + y_offset) / SCALE);
            if (noise[y][x] < min_val) min_val = noise[y][x];
            if (noise[y][x] > max_val) max_val = noise[y][x];
        }
    }

    // Normalisation entre 0 et 255
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            heightmap[y][x] = (unsigned char)(255.0f * (noise[y][x] - min_val) / (max_val - min_val));
        }
    }
}

// Affichage ASCII amélioré
void print_heightmap(unsigned char heightmap[WIDTH][HEIGHT]) {
    const char levels[] = " .:-=+*#%@";
    int num_levels = sizeof(levels) - 1;

    for (int y = 0; y < HEIGHT; y += 8) {
        for (int x = 0; x < WIDTH; x += 4) {
            int val = heightmap[y][x];
            char c = levels[(val * num_levels) / 256];
            printf("%c", c);
        }
        printf("\n");
    }
}

int main() {
    unsigned char heightmap[WIDTH][HEIGHT];

    srand(42);
    generate_gradients();
    generate_heightmap(heightmap, 0, 0);
    print_heightmap(heightmap);
	// generate_heightmap(heightmap, 0, 200);
    // print_heightmap(heightmap);
	// generate_heightmap(heightmap, 0, 400);
    // print_heightmap(heightmap);

    return 0;
}
