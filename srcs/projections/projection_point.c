/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_point.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:16:14 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/10 11:04:42 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


#include <stdio.h>
void	calculate_point_projection(int x, int y, t_env *env)
{
	double	matrix[3][3];
	double	vector[4];
	double	perspective;

	vector[0] = x - env->camera->proj_x;
	vector[1] = y - env->camera->proj_y;
	
	// add pseudo x and y axes
	if (x == 0 && y == 0){vector[0] = 0 - env->camera->proj_x;vector[1] = 0 - env->camera->proj_y;}else if (x == 1 && y == 0){vector[0] = 100 - env->camera->proj_x;vector[1] = 0 - env->camera->proj_y;}else if (x == 0 && y == 1){vector[0] = 0 - env->camera->proj_x;vector[1] = 110 - env->camera->proj_y;}
	
	vector[2] = (env->map->map[y][x] - env->camera->proj_z) * env->z_ratio;
	init_roll_matrix(matrix, env->camera->roll);
	vector_multiply_matrix_3x3(matrix, vector);
	init_pitch_matrix(matrix, env->camera->pitch);
	vector_multiply_matrix_3x3(matrix, vector);
	init_yaw_matrix(matrix, env->camera->yaw);
	vector_multiply_matrix_3x3(matrix, vector);
	vector[3] = 1;
	env->point_list[y * env->map->length + x].x = (int)((vector[0] / perspective) * env->camera->scale) + WIN_WIDTH / 2; // + WIN_WIDTH / 2
	env->point_list[y * env->map->length + x].y = (int)((vector[1] / perspective) * env->camera->scale) + WIN_HEIGHT / 2; // + WIN_HEIGHT / 2
	env->point_list[y * env->map->length + x].z = vector[2];
	env->point_list[y * env->map->length + x].color = env->map->color_map[y][x];




	if (x == 0 && y == 0)
		env->point_list[y * env->map->length + x].color = 0xffffff;
	else if (x == 1 && y == 0)
		env->point_list[y * env->map->length + x].color = 0xff0000;
	else if (x == 0 && y == 1)
		env->point_list[y * env->map->length + x].color = 0x00ff00;
}
 