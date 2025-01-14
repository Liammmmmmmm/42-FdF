/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_point.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:16:14 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/14 10:36:14 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_homogenous_vector(double vector[4], t_env *env, int x, int y)
{
	double	matrix[3][3];

	vector[0] = x - env->camera->proj_x;
	vector[1] = y - env->camera->proj_y;
	vector[2] = (-env->map->map[y][x] - env->camera->proj_z) * env->z_ratio;
	init_roll_matrix(matrix, env->camera->roll);
	vector_multiply_matrix_3x3(matrix, vector);
	init_yaw_matrix(matrix, env->camera->yaw);
	vector_multiply_matrix_3x3(matrix, vector);
	init_pitch_matrix(matrix, env->camera->pitch);
	vector_multiply_matrix_3x3(matrix, vector);
	vector[3] = 1;
}

void	set_projection_type(double vector[4], t_env *env, int x, int y)
{
	double	proj_matrix[4][4];

	if (env->perspective == 1)
		init_perspective_matrix(proj_matrix, env);
	else if (env->perspective == 0)
		init_orthogonal_matrix(proj_matrix, env);
	if (env->perspective != 2)
	{
		vector_multiply_matrix_4x4(proj_matrix, vector);
		env->point_list[y * env->map->length + x].x
			= (int)(((vector[0] / vector[3] + 1) / 2) * WIN_WIDTH);
		env->point_list[y * env->map->length + x].y
			= (int)(((1 - (vector[1] / vector[3])) / 2) * WIN_HEIGHT);
	}
	else
	{
		env->point_list[y * env->map->length + x].x
			= (int)(vector[0] * env->camera->scale + WIN_WIDTH / 2);
		env->point_list[y * env->map->length + x].y
			= (int)(vector[1] * env->camera->scale + WIN_HEIGHT / 2);
	}
}

void	calculate_point_projection(int x, int y, t_env *env)
{
	double	vector[4];

	get_homogenous_vector(vector, env, x, y);
	set_projection_type(vector, env, x, y);
	env->point_list[y * env->map->length + x].z = vector[2] / vector[3];
	if (env->point_list[y * env->map->length + x].z > 0 && vector[3] < 0)
		env->point_list[y * env->map->length + x].z = vector[2] / -vector[3];
	env->point_list[y * env->map->length + x].color = env->map->color_map[y][x];
	if (env->color_by_height)
		env->point_list[y * env->map->length + x].color
			= calc_gradiant_color(
				COLOR_MIN,
				COLOR_MAX,
				(double)env->map->map[y][x] / env->map->highest);
}
