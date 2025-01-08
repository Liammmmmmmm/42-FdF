/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:07:24 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/08 13:59:39 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_yaw_matrix(double matrix[3][3], double yaw)
{
	matrix[0][0] = cos(yaw);
	matrix[0][1] = -sin(yaw);
	matrix[0][2] = 0;
	matrix[1][0] = sin(yaw);
	matrix[1][1] = cos(yaw);
	matrix[1][2] = 0;
	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = 1;
}

void	init_pitch_matrix(double matrix[3][3], double pitch)
{
	matrix[0][0] = 1;
	matrix[0][1] = 0;
	matrix[0][2] = 0;
	matrix[1][0] = 0;
	matrix[1][1] = cos(pitch);
	matrix[1][2] = -sin(pitch);
	matrix[2][0] = 0;
	matrix[2][1] = sin(pitch);
	matrix[2][2] = cos(pitch);
}

void	init_roll_matrix(double matrix[3][3], double roll)
{
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

void	vector_multiply_matrix(double matrix[3][3], double v[3])
{
	double res[3];
	
	res[0] = v[0] * matrix[0][0] + v[1] * matrix[0][1] + v[2] * matrix[0][2];
	res[1] = v[0] * matrix[1][0] + v[1] * matrix[1][1] + v[2] * matrix[1][2];
	res[2] = v[0] * matrix[2][0] + v[1] * matrix[2][1] + v[2] * matrix[2][2];
	v[0] = res[0];
	v[1] = res[1];
	v[2] = res[2];
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
