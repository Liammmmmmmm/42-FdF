/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_point.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:16:14 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/06 17:32:53 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	*calculate_point_projection(int x, int y, t_map *map, t_camera *cam)
{
	t_point *point;
	double	matrix[3][3];
	double	vector[3];

	
	point = malloc(sizeof(t_point));
	if (!point)
		return (NULL);
	vector[0] = x - cam->proj_x;
	vector[1] = y - cam->proj_y;
	vector[2] = map->map[y][x] - cam->proj_z;
	init_yaw_matrix(matrix, cam->yaw);
	vector_multiply_matrix(matrix, vector);
	init_pitch_matrix(matrix, cam->pitch);
	vector_multiply_matrix(matrix, vector);
	init_roll_matrix(matrix, cam->roll);
	vector_multiply_matrix(matrix, vector);
	point->x = (int)((vector[0]) * cam->scale);
	point->y = (int)((vector[1]) * cam->scale);
	point->color = map->color_map[y][x];
	return (point);
}
