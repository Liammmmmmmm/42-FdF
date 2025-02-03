/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:18:42 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/03 13:18:40 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_camera_distance(t_env *env, double new_distance)
{
	env->camera->distance = new_distance;
	env->camera->scale = calc_scale(env->map, env->camera);
	calc_cam_proj(env, env->camera);
	env->camera->mouse_sensibility
		= env->mouse_sensibility / (env->camera->distance + 1);
}

void	zoom(t_env *env, int direction)
{
	if (direction == SCROLL_UP && env->camera->distance > 0.1)
	{
		if (env->camera->distance <= 1)
			change_camera_distance(env, env->camera->distance - 0.1);
		else
			change_camera_distance(env, env->camera->distance - 1.0);
	}
	else if (direction == SCROLL_DOWN)
	{
		if (env->camera->distance < 1)
			change_camera_distance(env, env->camera->distance + 0.1);
		else
			change_camera_distance(env, env->camera->distance + 1.0);
	}
}

void	rotate(int x, int y, t_env *env)
{
	int	dx;
	int	dy;

	dx = -(x - env->mouse_last_x);
	dy = y - env->mouse_last_y;
	env->camera->yaw += dx * env->camera->mouse_sensibility;
	env->camera->pitch += dy * env->camera->mouse_sensibility;
	if (env->camera->pitch > PI_10D)
		env->camera->pitch = -PI_10D;
	if (env->camera->pitch < -PI_10D)
		env->camera->pitch = PI_10D;
	if (env->camera->yaw > PI_10D)
		env->camera->yaw = -PI_10D;
	if (env->camera->yaw < -PI_10D)
		env->camera->yaw = PI_10D;
	calc_cam_proj(env, env->camera);
}

void	roll(int direction, t_env *env)
{
	env->camera->roll += direction * 0.1;
	if (env->camera->roll > PI_10D)
		env->camera->roll = -PI_10D;
	if (env->camera->roll < -PI_10D)
		env->camera->roll = PI_10D;
	calc_cam_proj(env, env->camera);
}

void	translate(int x, int y, t_env *env)
{
	int		dx;
	int		dy;
	double	local_axes[3][3];
	double	delta_cam_move[3];

	get_local_axes(local_axes, env->camera->yaw,
		env->camera->pitch, env->camera->roll, env);
	dx = x - env->mouse_last_x;
	dy = y - env->mouse_last_y;

	delta_cam_move[0] = dx * local_axes[2][0] - dy * local_axes[1][0];
	delta_cam_move[1] = dx * local_axes[2][1] - dy * local_axes[1][1];
	delta_cam_move[2] = dx * local_axes[2][2] - dy * local_axes[1][2];
	env->camera->x += delta_cam_move[0] * env->mouse_sensibility
		* env->camera->distance / 100;
	env->camera->y += delta_cam_move[1] * env->mouse_sensibility
		* env->camera->distance / 100;
	env->camera->z += delta_cam_move[2] * env->mouse_sensibility
		* env->camera->distance / 100;
	calc_cam_proj(env, env->camera);
}
