/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_point.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:16:14 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/08 18:39:55 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


#include <stdio.h>
void	calculate_point_projection(int x, int y, t_env *env)
{
	double	matrix[3][3];
	double	vector[3];
	double	perspective;

	vector[0] = x - env->camera->proj_x;
	vector[1] = y - env->camera->proj_y;
	vector[2] = (env->map->map[y][x] - env->camera->proj_z) * env->z_ratio;
	init_yaw_matrix(matrix, env->camera->yaw);
	vector_multiply_matrix(matrix, vector);
	init_pitch_matrix(matrix, env->camera->pitch);
	vector_multiply_matrix(matrix, vector);
	init_roll_matrix(matrix, env->camera->roll);
	vector_multiply_matrix(matrix, vector);
	perspective = 1;
	if (env->perspective && vector[2] > 0.01)
		perspective = vector[2];
	env->point_list[y * env->map->length + x]->x = (int)((vector[0] / perspective) * env->camera->scale) + WIN_WIDTH / 2;
	env->point_list[y * env->map->length + x]->y = (int)((vector[1] / perspective) * env->camera->scale) + WIN_HEIGHT / 2;
	env->point_list[y * env->map->length + x]->z = env->map->map[y][x];
	env->point_list[y * env->map->length + x]->color = env->map->color_map[y][x];
}
 