/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:07:24 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/03 16:54:58 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_yaw_matrix(double matrix[3][3], t_calc_trigo trigo_calcs)
{
	matrix[0][0] = trigo_calcs.cos_yaw;
	matrix[0][1] = -trigo_calcs.sin_yaw;
	matrix[0][2] = 0;
	matrix[1][0] = trigo_calcs.sin_yaw;
	matrix[1][1] = trigo_calcs.cos_yaw;
	matrix[1][2] = 0;
	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = 1;
}

void	init_roll_matrix(double matrix[3][3], t_calc_trigo trigo_calcs)
{
	matrix[0][0] = trigo_calcs.cos_roll;
	matrix[0][1] = 0;
	matrix[0][2] = trigo_calcs.sin_roll;
	matrix[1][0] = 0;
	matrix[1][1] = 1;
	matrix[1][2] = 0;
	matrix[2][0] = -trigo_calcs.sin_roll;
	matrix[2][1] = 0;
	matrix[2][2] = trigo_calcs.cos_roll;
}

void	init_pitch_matrix(double matrix[3][3], t_calc_trigo trigo_calcs)
{
	matrix[0][0] = 1;
	matrix[0][1] = 0;
	matrix[0][2] = 0;
	matrix[1][0] = 0;
	matrix[1][1] = trigo_calcs.cos_pitch;
	matrix[1][2] = -trigo_calcs.sin_pitch;
	matrix[2][0] = 0;
	matrix[2][1] = trigo_calcs.sin_pitch;
	matrix[2][2] = trigo_calcs.cos_pitch;
}

void	init_perspective_matrix(double matrix[4][4], t_env *env)
{
	double	focale;

	focale = 1 / tan(env->camera->fov * (PI_10D / 180) / 2);
	matrix[0][0] = focale / (WIN_WIDTH / WIN_HEIGHT);
	matrix[0][1] = 0;
	matrix[0][2] = 0;
	matrix[0][3] = 0;
	matrix[1][0] = 0;
	matrix[1][1] = focale;
	matrix[1][2] = 0;
	matrix[1][3] = 0;
	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = (env->camera->zfar + env->camera->znear) / (env->camera->znear - env->camera->zfar);
	matrix[2][3] = 2 * env->camera->zfar * env->camera->znear / (env->camera->znear - env->camera->zfar);
	matrix[3][0] = 0;
	matrix[3][1] = 0;
	matrix[3][2] = -1;
	matrix[3][3] = 0;
}

void	init_orthogonal_matrix(double matrix[4][4], t_env *env)
{
	matrix[0][0] = 2 / (env->camera->right - env->camera->left);
	matrix[0][1] = 0;
	matrix[0][2] = 0;
	matrix[0][3] = (-env->camera->right + env->camera->left) / (env->camera->right - env->camera->left);
	matrix[1][0] = 0;
	matrix[1][1] = 2 / (env->camera->top - env->camera->bottom);
	matrix[1][2] = 0;
	matrix[1][3] = (-env->camera->top + env->camera->bottom) / (env->camera->top - env->camera->bottom);
	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = -2 / (env->camera->far - env->camera->near);
	matrix[2][3] = (-env->camera->far + env->camera->near) / (env->camera->far - env->camera->near);
	matrix[3][0] = 0;
	matrix[3][1] = 0;
	matrix[3][2] = 0;
	matrix[3][3] = 1;
}
