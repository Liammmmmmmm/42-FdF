/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_point.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:16:14 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/07 13:25:11 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	calculate_point_projection(int x, int y, t_env *env)
{
	double	matrix[3][3];
	double	vector[3];

	vector[0] = x - env->camera->proj_x;
	vector[1] = y - env->camera->proj_y;
	vector[2] =env->map->map[y][x] -env->camera->proj_z;
	init_yaw_matrix(matrix,env->camera->yaw);
	vector_multiply_matrix(matrix, vector);
	init_pitch_matrix(matrix,env->camera->pitch);
	vector_multiply_matrix(matrix, vector);
	init_roll_matrix(matrix,env->camera->roll);
	vector_multiply_matrix(matrix, vector);
	env->point_list[y * env->map->length + x]->x = (int)((vector[0]) *env->camera->scale);
	env->point_list[y * env->map->length + x]->y = (int)((vector[1]) *env->camera->scale);
	env->point_list[y * env->map->length + x]->color =env->map->color_map[y][x];
}
