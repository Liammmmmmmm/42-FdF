/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_movements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:00:39 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/14 13:57:38 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_key(int key, int *local_x, int *local_y, int *local_z)
{
	if (key == KEY_W)
		*local_z = -1;
	else if (key == KEY_S)
		*local_z = 1;
	else if (key == KEY_A)
		*local_x = -1;
	else if (key == KEY_D)
		*local_x = 1;
	else if (key == KEY_SHIFT)
		*local_y = -1;
	else if (key == KEY_SPACE)
		*local_y = 1;
}

void	wasd_move(int key, t_env *env)
{
	double	a[3][3];
	double	delta_move[3];
	int		local_x;
	int		local_y;
	int		local_z;

	local_x = 0;
	local_y = 0;
	local_z = 0;
	init_key(key, &local_x, &local_y, &local_z);
	local_x *= env->camera->distance;
	local_y *= env->camera->distance;
	local_z *= env->camera->distance;
	get_local_axes(a, env->camera->pitch, env->camera->yaw, env->camera->roll);
	delta_move[0] = local_x * a[0][0] + local_y * a[1][0] + local_z * a[2][0];
	delta_move[1] = local_x * a[0][1] + local_y * a[1][1] + local_z * a[2][1];
	delta_move[2] = local_x * a[0][2] + local_y * a[1][2] + local_z * a[2][2];
	env->camera->x += delta_move[0] * env->mouse_sensibility
		* env->camera->distance / 100;
	env->camera->y += delta_move[1] * env->mouse_sensibility
		* env->camera->distance / 100;
	env->camera->z += delta_move[2] * env->mouse_sensibility
		* env->camera->distance / 100;
	calc_cam_proj(env, env->camera);
}
