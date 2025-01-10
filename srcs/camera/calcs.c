/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:20:17 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/10 15:54:13 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void get_local_axes(double axes[3][3], double yaw, double pitch, double roll)
{
	double	yaw_matrix[3][3];
	double	pitch_matrix[3][3];
	double	roll_matrix[3][3];
	double	temp_matrix[3][3];

    init_yaw_matrix(yaw_matrix, yaw);
    init_pitch_matrix(pitch_matrix, pitch);
    init_roll_matrix(roll_matrix, roll);
    multiply_matrix_3x3(temp_matrix, roll_matrix, pitch_matrix);
    multiply_matrix_3x3(axes, temp_matrix, yaw_matrix);
}


void	calc_cam_proj(t_env *env, t_camera *camera)
{
	if (env->cam_around_focus == 1)
	{
		camera->proj_x = camera->x + camera->distance * cos(camera->pitch) * cos(camera->yaw);				
		camera->proj_y = camera->y + camera->distance * cos(camera->pitch) * sin(camera->yaw);
		camera->proj_z = camera->z + camera->distance * sin(camera->pitch);
	}
	else
	{
		camera->proj_x = camera->x;
		camera->proj_y = camera->y;
		camera->proj_z = camera->z;
	}
	// printf("distance : %.6f | focus : x:%.6f, y:%.6f, z:%.6f | proj x:%.6f, y:%.6f, z:%.6f | pitch:%.6f, yaw:%.6f, roll:%.6f\n", camera->distance, camera->x, camera->y, camera->z, camera->proj_x, camera->proj_y, camera->proj_z, camera->pitch, camera->yaw, camera->roll);
}

double	calc_scale(t_map *map, t_camera *camera)
{
	double depth_factor = camera->distance / 10.0;
	double scale = WIN_WIDTH / depth_factor;
	double map_size = sqrt(map->length * map->height);
	
	scale /= map_size;

	return scale;
}
