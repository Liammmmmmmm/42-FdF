/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_movements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:00:39 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/05 12:07:42 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void wasd_move(int key, t_env *env) {
	t_camera *cam = env->camera;
	double  (*axes)[3] = env->camera->local_axes;

	if (key == KEY_W)
	{
		cam->x += axes[0][0] * cam->distance / 10;
		cam->y += axes[0][1] * cam->distance / 10;
		cam->z += axes[0][2] * cam->distance / 10;
	}
	else if (key == KEY_S)
	{
		cam->x -= axes[0][0] * cam->distance / 10;
		cam->y -= axes[0][1] * cam->distance / 10;
		cam->z -= axes[0][2] * cam->distance / 10;
	}
	else if (key == KEY_A)
	{
		cam->x -= axes[2][0] * cam->distance / 10;
		cam->y -= axes[2][1] * cam->distance / 10;
		cam->z -= axes[2][2] * cam->distance / 10;
	}
	else if (key == KEY_D)
	{
		cam->x += axes[2][0] * cam->distance / 10;
		cam->y += axes[2][1] * cam->distance / 10;
		cam->z += axes[2][2] * cam->distance / 10;
	}
	else if (key == KEY_SPACE)
	{
		cam->x += axes[1][0] * cam->distance / 10;
		cam->y += axes[1][1] * cam->distance / 10;
		cam->z += axes[1][2] * cam->distance / 10;
	}
	else if (key == KEY_SHIFT)
	{
		cam->x -= axes[1][0] * cam->distance / 10;
		cam->y -= axes[1][1] * cam->distance / 10;
		cam->z -= axes[1][2] * cam->distance / 10;
	}
	calc_cam_proj(env, env->camera);
}
