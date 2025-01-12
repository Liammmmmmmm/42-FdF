/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:07:24 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/12 11:48:23 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// // axe z
// void	init_yaw_matrix(double matrix[3][3], double yaw)
// {
// 	matrix[0][0] = cos(yaw);
// 	matrix[0][1] = -sin(yaw);
// 	matrix[0][2] = 0;
// 	matrix[1][0] = sin(yaw);
// 	matrix[1][1] = cos(yaw);
// 	matrix[1][2] = 0;
// 	matrix[2][0] = 0;
// 	matrix[2][1] = 0;
// 	matrix[2][2] = 1;
// }

// // axe x
// void init_pitch_matrix(double matrix[3][3], double pitch) {
// 	matrix[0][0] = cos(pitch);
// 	matrix[0][1] = 0;
// 	matrix[0][2] = sin(pitch);
// 	matrix[1][0] = 0;
// 	matrix[1][1] = 1;
// 	matrix[1][2] = 0;
// 	matrix[2][0] = -sin(pitch);
// 	matrix[2][1] = 0;
// 	matrix[2][2] = cos(pitch);
// }

// // axe y
// void init_roll_matrix(double matrix[3][3], double roll) {
// 	matrix[0][0] = 1;
// 	matrix[0][1] = 0;
// 	matrix[0][2] = 0;
// 	matrix[1][0] = 0;
// 	matrix[1][1] = cos(roll);
// 	matrix[1][2] = -sin(roll);
// 	matrix[2][0] = 0;
// 	matrix[2][1] = sin(roll);
// 	matrix[2][2] = cos(roll);
// }

// // axe y
// void	init_pitch_matrix(double matrix[3][3], double pitch) {
// 	matrix[0][0] = 1;
// 	matrix[0][1] = 0;
// 	matrix[0][2] = 0;
// 	matrix[1][0] = 0;
// 	matrix[1][1] = cos(pitch);
// 	matrix[1][2] = -sin(pitch);
// 	matrix[2][0] = 0;
// 	matrix[2][1] = sin(pitch);
// 	matrix[2][2] = cos(pitch);
// }

// // axe x
// void	init_roll_matrix(double matrix[3][3], double roll) {
// 	matrix[0][0] = cos(roll);
// 	matrix[0][1] = 0;
// 	matrix[0][2] = sin(roll);
// 	matrix[1][0] = 0;
// 	matrix[1][1] = 1;
// 	matrix[1][2] = 0;
// 	matrix[2][0] = -sin(roll);
// 	matrix[2][1] = 0;
// 	matrix[2][2] = cos(roll);
// }


// axe x
void init_pitch_matrix(double matrix[3][3], double pitch) {
	pitch = pitch - PI_10D / 2;
	matrix[0][0] = cos(pitch);
	matrix[0][1] = -sin(pitch);
	matrix[0][2] = 0;
	matrix[1][0] = sin(pitch);
	matrix[1][1] = cos(pitch);
	matrix[1][2] = 0;
	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = 1;
}

// axe y
void init_roll_matrix(double matrix[3][3], double roll) {
	matrix[0][0] = cos(roll);
	matrix[0][1] = 0;
	matrix[0][2] = sin(roll);
	matrix[1][0] = 0;
	matrix[1][1] = 1;
	matrix[1][2] = 0;
	matrix[2][0] = -sin(roll);
	matrix[2][1] = 0;
	matrix[2][2] = cos(roll);
}

// axe z
void	init_yaw_matrix(double matrix[3][3], double yaw)
{
	yaw = yaw + PI_10D / 2;
	matrix[0][0] = 1;
	matrix[0][1] = 0;
	matrix[0][2] = 0;
	matrix[1][0] = 0;
	matrix[1][1] = cos(yaw);
	matrix[1][2] = -sin(yaw);
	matrix[2][0] = 0;
	matrix[2][1] = sin(yaw);
	matrix[2][2] = cos(yaw);
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

void	vector_multiply_matrix_3x3(double matrix[3][3], double v[3])
{
	double res[3];
	
	res[0] = v[0] * matrix[0][0] + v[1] * matrix[0][1] + v[2] * matrix[0][2];
	res[1] = v[0] * matrix[1][0] + v[1] * matrix[1][1] + v[2] * matrix[1][2];
	res[2] = v[0] * matrix[2][0] + v[1] * matrix[2][1] + v[2] * matrix[2][2];
	v[0] = res[0];
	v[1] = res[1];
	v[2] = res[2];
}

void	vector_multiply_matrix_4x4(double matrix[4][4], double v[4])
{
	double res[4];
	
	res[0] = v[0] * matrix[0][0] + v[1] * matrix[0][1] + v[2] * matrix[0][2] + v[3] * matrix[0][3];
	res[1] = v[0] * matrix[1][0] + v[1] * matrix[1][1] + v[2] * matrix[1][2] + v[3] * matrix[1][3];
	res[2] = v[0] * matrix[2][0] + v[1] * matrix[2][1] + v[2] * matrix[2][2] + v[3] * matrix[2][3];
	res[3] = v[0] * matrix[2][0] + v[1] * matrix[2][1] + v[2] * matrix[2][2] + v[3] * matrix[3][3];
	v[0] = res[0];
	v[1] = res[1];
	v[2] = res[2];
	v[3] = res[3];
}

void	multiply_matrix_3x3(double res[3][3], double a[3][3], double b[3][3])
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			res[i][j] = 0;
			k = -1;
			while (++k < 3)
				res[i][j] += a[i][k] * b[k][j];
		}
	}
}
