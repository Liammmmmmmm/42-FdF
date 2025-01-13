/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_calc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:51:30 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/13 19:00:02 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	res[0][0] = a[0][0] * b[0][0] + a[0][1] * b[1][0] + a[0][2] * b[2][0];
	res[0][1] = a[0][0] * b[0][1] + a[0][1] * b[1][1] + a[0][2] * b[2][1];
	res[0][2] = a[0][0] * b[0][2] + a[0][1] * b[1][2] + a[0][2] * b[2][2];
	res[1][0] = a[1][0] * b[0][0] + a[1][1] * b[1][0] + a[1][2] * b[2][0];
	res[1][1] = a[1][0] * b[0][1] + a[1][1] * b[1][1] + a[1][2] * b[2][1];
	res[1][2] = a[1][0] * b[0][2] + a[1][1] * b[1][2] + a[1][2] * b[2][2];
	res[2][0] = a[2][0] * b[0][0] + a[2][1] * b[1][0] + a[2][2] * b[2][0];
	res[2][1] = a[2][0] * b[0][1] + a[2][1] * b[1][1] + a[2][2] * b[2][1];
	res[2][2] = a[2][0] * b[0][2] + a[2][1] * b[1][2] + a[2][2] * b[2][2];
}
