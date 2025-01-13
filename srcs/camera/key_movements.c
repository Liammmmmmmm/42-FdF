/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_movements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:00:39 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/13 16:34:54 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	wasd_move(int key, t_env *env)
{
	double	local_axes[3][3];
	double	delta_cam_move[3];
	int		local_x;
	int		local_y;
	int		local_z;

	local_x = 0;
	local_y = 0;
	local_z = 0;
	if (key == KEY_W)
		local_z = -1 * env->camera->distance;
	else if (key == KEY_S)
		local_z = 1 * env->camera->distance;
	else if (key == KEY_A)
		local_x = -1 * env->camera->distance;
	else if (key == KEY_D)
		local_x = 1 * env->camera->distance;
	else if (key == KEY_SHIFT)
		local_y = -1 * env->camera->distance;
	else if (key == KEY_SPACE)
		local_y = 1 * env->camera->distance;
	get_local_axes(local_axes, env->camera->pitch, env->camera->yaw, env->camera->roll);
	delta_cam_move[0] = local_x * local_axes[0][0] + local_y * local_axes[1][0] + local_z * local_axes[2][0];
    delta_cam_move[1] = local_x * local_axes[0][1] + local_y * local_axes[1][1] + local_z * local_axes[2][1];
	delta_cam_move[2] = local_x * local_axes[0][2] + local_y * local_axes[1][2] + local_z * local_axes[2][2];
	env->camera->x += delta_cam_move[0] * env->mouse_sensibility * env->camera->distance / 100;
	env->camera->y += delta_cam_move[1] * env->mouse_sensibility * env->camera->distance / 100;
	env->camera->z += delta_cam_move[2] * env->mouse_sensibility * env->camera->distance / 100;
	calc_cam_proj(env, env->camera);
}
