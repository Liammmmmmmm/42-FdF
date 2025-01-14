/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:20:17 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/14 11:50:15 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_local_axes(double axes[3][3], double yaw, double pitch, double roll)
{
	double	yaw_matrix[3][3];
	double	pitch_matrix[3][3];
	double	roll_matrix[3][3];
	double	temp_matrix[3][3];

	init_pitch_matrix(yaw_matrix, yaw);
	init_yaw_matrix(pitch_matrix, pitch);
	init_roll_matrix(roll_matrix, roll);
	multiply_matrix_3x3(temp_matrix, yaw_matrix, pitch_matrix);
	multiply_matrix_3x3(axes, temp_matrix, roll_matrix);
}

void	calc_cam_proj(t_env *env, t_camera *cam)
{
	if (env->cam_around_focus == 1)
	{
		cam->proj_x = cam->x + cam->distance * cos(cam->yaw) * cos(cam->pitch);
		cam->proj_y = cam->y + cam->distance * cos(cam->yaw) * sin(cam->pitch);
		cam->proj_z = cam->z + cam->distance * sin(cam->yaw);
	}
	else
	{
		cam->proj_x = cam->x;
		cam->proj_y = cam->y;
		cam->proj_z = cam->z;
	}
}

double	calc_scale(t_map *map, t_camera *camera)
{
	double	depth_factor;
	double	scale;
	double	map_size;

	depth_factor = camera->distance / 10.0;
	map_size = sqrt(map->length * map->height);
	scale = WIN_WIDTH / depth_factor / map_size;
	return (scale);
}
