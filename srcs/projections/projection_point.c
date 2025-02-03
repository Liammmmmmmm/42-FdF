/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_point.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:16:14 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/03 17:00:19 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	transform_to_spherical(double vector[4], t_env *env, int x, int y)
{
	double	r;
	double	lamda;
	double	phi;

	vector[0] = x - env->map->length / 2;
	vector[1] = y - env->map->height / 2;
	vector[2] = env->map->map[y][x] * env->z_ratio;
	r = env->map->length / (2 * PI_10D);
	if (r == 0)
		r = 1;
	lamda = -PI_10D + (2 * PI_10D) * x / (env->map->length - 1);
	phi = -PI_10D / 2 + PI_10D * y / (env->map->height - 1);
	r = r + (env->map->map[y][x] * env->z_ratio * 0.1);
	vector[0] = r * cos(phi) * sin(lamda);
	vector[1] = r * cos(phi) * cos(lamda);
	vector[2] = r * sin(phi);
	if (env->cam_around_focus == 0)
	{
		vector[0] = vector[0] - env->camera->proj_x;
		vector[1] = vector[1] - env->camera->proj_y;
		vector[2] = vector[2] - env->camera->proj_z;
	}
}

void	get_homogenous_vector(double vector[4], t_env *env, int x, int y, t_calc_trigo trigo_calcs)
{
	double	matrix[3][3];

	if (env->perspective == 2)
	{
		vector[0] = x - env->camera->x;
		vector[1] = y - env->camera->y;
		vector[2] = (-env->map->map[y][x] + env->camera->z) * env->z_ratio;
	}
	else
	{
		vector[0] = x - env->camera->proj_x;
		vector[1] = y - env->camera->proj_y;
		vector[2] = (-env->map->map[y][x] + env->camera->proj_z) * env->z_ratio;
	}
	if (env->sphere_proj)
		transform_to_spherical(vector, env, x, y);
	init_roll_matrix(matrix, trigo_calcs);
	vector_multiply_matrix_3x3(matrix, vector);
	init_yaw_matrix(matrix, trigo_calcs);
	vector_multiply_matrix_3x3(matrix, vector);
	init_pitch_matrix(matrix, trigo_calcs);
	vector_multiply_matrix_3x3(matrix, vector);
	vector[3] = 1;
}

void	set_projection_type(double vector[4], t_env *env, int x, int y)
{
	if (env->perspective != 2)
	{
		vector_multiply_matrix_4x4(env->camera->perspective, vector);
		env->point_list[y * env->map->length + x].x = (int)(((vector[0] / vector[3] + 1) / 2) * WIN_WIDTH);
		env->point_list[y * env->map->length + x].y = (int)(((1 - (vector[1] / vector[3])) / 2) * WIN_HEIGHT);
	}
	else
	{
		env->point_list[y * env->map->length + x].x = (int)(vector[0] * env->camera->scale + WIN_WIDTH / 2);
		env->point_list[y * env->map->length + x].y = (int)(vector[1] * env->camera->scale + WIN_HEIGHT / 2);
	}
}

void	calculate_point_projection(int x, int y, t_env *env, t_calc_trigo trigo_calcs)
{
	double	vector[4];

	get_homogenous_vector(vector, env, x, y, trigo_calcs);
	set_projection_type(vector, env, x, y);
	env->point_list[y * env->map->length + x].z = vector[2] / vector[3];
	if (env->point_list[y * env->map->length + x].z > 0 && vector[3] < 0)
		env->point_list[y * env->map->length + x].z = vector[2] / -vector[3];
	env->point_list[y * env->map->length + x].color = env->map->color_map[y][x];

	if (env->custom_color)
		env->point_list[y * env->map->length + x].color = get_color_by_preset(env, x, y);
}
