/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:20:17 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/31 12:18:40 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_local_axes(double axes[3][3], double yaw, double pitch, double roll)
{
	double cos_yaw = cos(yaw);
	double sin_yaw = sin(yaw);
	double cos_pitch = cos(pitch);
	double sin_pitch = sin(pitch);
	double cos_roll = cos(roll);
	double sin_roll = sin(roll);

	// Forward
	axes[0][0] = cos_yaw * cos_pitch;
	axes[0][1] = sin_yaw * cos_pitch;
	axes[0][2] = sin_pitch;

	// Up
	axes[1][0] = (-cos_yaw * sin_pitch * cos_roll) + (-sin_yaw * sin_roll);
	axes[1][1] = (-sin_yaw * sin_pitch * cos_roll) + (cos_yaw * sin_roll);
	axes[1][2] = cos_pitch * cos_roll;

	// Right
	axes[2][0] = -sin_yaw * cos_roll - cos_yaw * sin_pitch * sin_roll;
	axes[2][1] = cos_yaw * cos_roll - sin_yaw * sin_pitch * sin_roll;
	axes[2][2] = cos_pitch * sin_roll;
}

void	calc_cam_proj(t_env *env, t_camera *cam)
{
	if (env->cam_around_focus == 1)
	{
		cam->proj_x = cam->x + cam->distance * cos(cam->pitch) * cos(cam->yaw);
		cam->proj_y = cam->y + cam->distance * cos(cam->pitch) * sin(cam->yaw);
		cam->proj_z = cam->z + cam->distance * sin(cam->pitch);
		if (env->perspective == 1)
		{
			cam->proj_x = -cam->proj_x;
			cam->proj_z = -cam->proj_z;
		}
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
