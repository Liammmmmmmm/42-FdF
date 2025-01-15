/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:51:34 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/15 17:14:16 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	calculate_every_projection(t_env *env)
{
	int	y;
	int	x;

	y = -1;
	while (++y < env->map->height)
	{
		x = -1;
		while (++x < env->map->length)
			calculate_point_projection(x, y, env);
	}
}

char	*info_string(t_env *env)
{
	char	*perspective;

	if (env->perspective == 1)
		perspective = "Perspective\0";
	else if (env->perspective == 0)
		perspective = "Orthogonale\0";
	else
		perspective = "Basic\0";
	return (params_to_string(LIVE_INFO, env->map->length, env->map->height,
			env->camera->yaw * 180 / PI_10D, env->camera->pitch * 180 / PI_10D,
			env->camera->roll * 180 / PI_10D, env->camera->x, env->camera->y,
			env->camera->z, env->camera->proj_x, env->camera->proj_y,
			env->camera->proj_z, env->camera->distance, env->camera->scale,
			env->camera->mouse_sensibility, env->camera->fov,
			env->camera->znear, env->camera->zfar, env->camera->right,
			env->camera->left, env->camera->top, env->camera->bottom,
			env->camera->near, env->camera->far, env->mouse_click_rotation,
			env->mouse_click_translation, env->mouse_sensibility,
			env->mouse_last_x, env->mouse_last_y, env->frames_gen,
			env->sphere_proj, perspective, env->z_ordering,
			!env->cam_around_focus, env->z_ratio));
}

void	display_infos_win(t_env *env)
{
	t_point	text_pos;
	char	*dynamic_infos;

	text_pos.x = 10;
	text_pos.y = 10;
	text_pos.color = 0xFFFFFF;
	if (env->display_infos == 2)
		string_to_img(env->img, env->font, text_pos, CONTROLS);
	if (env->display_infos == 1)
	{
		dynamic_infos = info_string(env);
		if (dynamic_infos)
			string_to_img(env->img, env->font, text_pos, dynamic_infos);
		free(dynamic_infos);
	}
}

void	render_frame(t_env *env)
{
	ft_bzero(env->img->img_str, WIN_WIDTH * WIN_HEIGHT * (env->img->bits / 8));
	calculate_every_projection(env);
	save_lines(env);
	if (env->z_ordering)
		quicksort_lines(env->lines, 0, env->line_amount - 1, 0);
	draw_every_lines(env);
	display_infos_win(env);
	mlx_put_image_to_window(env->mlx, env->mlx_win, env->img->img, 0, 0);
	env->frames_gen += 1;
}
