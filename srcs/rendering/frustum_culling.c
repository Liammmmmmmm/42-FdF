/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frustum_culling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:35:10 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/03 18:41:47 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_view_matrix(double view[4][4], const double axes[3][3], t_env *env)
{
	view[0][0] = axes[2][0]; // Right
	view[0][1] = axes[2][1];
	view[0][2] = axes[2][2];
	view[0][3] = 0;

	view[1][0] = axes[1][0]; // Up
	view[1][1] = axes[1][1];
	view[1][2] = axes[1][2];
	view[1][3] = 0;

	view[2][0] = -axes[0][0]; // Forward
	view[2][1] = -axes[0][1];
	view[2][2] = -axes[0][2];
	view[2][3] = 0;

	// Matrice de translation
	view[3][0] = -(env->camera->x * view[0][0] + env->camera->z * view[1][0] + env->camera->y * view[2][0]);
	view[3][1] = -(env->camera->x * view[0][1] + env->camera->z * view[1][1] + env->camera->y * view[2][1]);
	view[3][2] = -(env->camera->x * view[0][2] + env->camera->z * view[1][2] + env->camera->y * view[2][2]);
	view[3][3] = 1;
}

void	extract_frustum_planes(t_frustum *frustum, double matrix[4][4])
{
	int	i;
	// Left : M3 + M0
	frustum->planes[0].a = matrix[0][3] + matrix[0][0];
	frustum->planes[0].b = matrix[1][3] + matrix[1][0];
	frustum->planes[0].c = matrix[2][3] + matrix[2][0];
	frustum->planes[0].d = matrix[3][3] + matrix[3][0];

	// Right : M3 - M0
	frustum->planes[1].a = matrix[0][3] - matrix[0][0];
	frustum->planes[1].b = matrix[1][3] - matrix[1][0];
	frustum->planes[1].c = matrix[2][3] - matrix[2][0];
	frustum->planes[1].d = matrix[3][3] - matrix[3][0];

	// Bottom : M3 + M1
	frustum->planes[2].a = matrix[0][3] + matrix[0][1];
	frustum->planes[2].b = matrix[1][3] + matrix[1][1];
	frustum->planes[2].c = matrix[2][3] + matrix[2][1];
	frustum->planes[2].d = matrix[3][3] + matrix[3][1];

	// Top : M3 - M1
	frustum->planes[3].a = matrix[0][3] - matrix[0][1];
	frustum->planes[3].b = matrix[1][3] - matrix[1][1];
	frustum->planes[3].c = matrix[2][3] - matrix[2][1];
	frustum->planes[3].d = matrix[3][3] - matrix[3][1];

	// Near : M3 + M2
	frustum->planes[4].a = matrix[0][3] + matrix[0][2];
	frustum->planes[4].b = matrix[1][3] + matrix[1][2];
	frustum->planes[4].c = matrix[2][3] + matrix[2][2];
	frustum->planes[4].d = matrix[3][3] + matrix[3][2];

	// Far : M3 - M2
	frustum->planes[5].a = matrix[0][3] - matrix[0][2];
	frustum->planes[5].b = matrix[1][3] - matrix[1][2];
	frustum->planes[5].c = matrix[2][3] - matrix[2][2];
	frustum->planes[5].d = matrix[3][3] - matrix[3][2];

	// Normalisation des plans
	i = 0;
	while (i < 6)
	{
		double	length = sqrt(frustum->planes[i].a * frustum->planes[i].a
							+ frustum->planes[i].b * frustum->planes[i].b
							+ frustum->planes[i].c * frustum->planes[i].c);
		if (length != 0.0)
		{
			frustum->planes[i].a /= length;
			frustum->planes[i].b /= length;
			frustum->planes[i].c /= length;
			frustum->planes[i].d /= length;
		}
		i++;
	}
}

int	is_point_in_frustum(const t_frustum *frustum, const t_vec3 *point)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		double distance = frustum->planes[i].a * point->x
						+ frustum->planes[i].b * point->y
						+ frustum->planes[i].c * point->z
						+ frustum->planes[i].d;
		if (distance < 0)
			return (0);
		i++;
	}
	return (1);
}

