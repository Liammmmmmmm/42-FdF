/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:20:17 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/05 14:05:14 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_local_axes(double axes[3][3], t_calc_trigo trigo, t_env *env)
{
	trigo.sin_yaw = sin(env->camera->yaw);
	trigo.cos_yaw = cos(env->camera->yaw);
	trigo.sin_pitch = sin(env->camera->pitch);
	trigo.cos_pitch = cos(env->camera->pitch);

	/*     Forward     */
	axes[0][0] = trigo.cos_yaw * trigo.cos_pitch;
	axes[0][1] = -trigo.sin_yaw * trigo.cos_pitch;
	axes[0][2] = -trigo.sin_pitch;

	/*       Up        */
	axes[1][0] = -((-trigo.cos_yaw * trigo.sin_pitch * trigo.cos_roll) + (-trigo.sin_yaw * trigo.sin_roll));
	axes[1][1] = ((-trigo.sin_yaw * trigo.sin_pitch * trigo.cos_roll) + (trigo.cos_yaw * trigo.sin_roll));
	axes[1][2] = trigo.cos_pitch * trigo.cos_roll;

	/*      Right      */ 
	axes[2][0] = -(-trigo.sin_yaw * trigo.cos_roll - trigo.cos_yaw * trigo.sin_pitch * trigo.sin_roll);
	axes[2][1] = (trigo.cos_yaw * trigo.cos_roll - trigo.sin_yaw * trigo.sin_pitch * trigo.sin_roll);
	axes[2][2] = -trigo.cos_pitch * trigo.sin_roll;

	if (env->perspective == 1)
	{
		axes[0][2] = -axes[0][2];
		axes[1][2] = -axes[1][2];
		axes[2][0] = -axes[2][0];
		axes[2][1] = -axes[2][1];
		axes[2][2] = -axes[2][2];
	}
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
