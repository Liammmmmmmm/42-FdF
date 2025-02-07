/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:51:34 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/07 16:12:44 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	calculate_every_projection(t_env *env)
{
	int				y;
	int				x;
	int				i;
	t_calc_trigo	trigo_calcs;

	trigo_calcs.sin_yaw = sin(env->camera->yaw + PI_10D / 2);
	trigo_calcs.cos_yaw = cos(env->camera->yaw + PI_10D / 2);
	trigo_calcs.sin_pitch = sin(env->camera->pitch - PI_10D / 2);
	trigo_calcs.cos_pitch = cos(env->camera->pitch - PI_10D / 2);
	trigo_calcs.sin_roll = sin(env->camera->roll);
	trigo_calcs.cos_roll = cos(env->camera->roll);

	get_local_axes(env->camera->local_axes, trigo_calcs, env);

	if (env->perspective == 1)
		init_perspective_matrix(env->camera->perspective, env);
	else if (env->perspective == 0)
		init_orthogonal_matrix(env->camera->perspective, env);
	/*
	if (env->perspective == 1)
	{
		double	view_matrix[4][4];
		double	view_perspective[4][4];
		
		init_view_matrix(view_matrix, env->camera->local_axes, env);
		multiply_matrix_4x4(view_perspective, env->camera->perspective, view_matrix);
		extract_frustum_planes(&env->camera->frustum, view_perspective);
	}
	*/
	i = 0;
	while (i < env->proc_amount)
	{
		env->threads_params[i].trigo_calcs = trigo_calcs;
		i++;
	}
	i = 0;
	while (i < env->proc_amount)
	{
		if (pthread_create(&env->threads[i], NULL, &thread_calc_projection, &env->threads_params[i]) != 0)
			break ;
		else
			y = env->threads_params[i].end - 1;
		i++;
	}
	while (++y < env->map->height)
	{
		if (y % env->points_reduction_factor == 0)
		{
			x = -1;
			while (++x < env->map->length)
				if (x % env->points_reduction_factor == 0)
					calculate_point_projection(x, y, env, trigo_calcs);
		}
	}
	while (i > 0)
	{
		pthread_join(env->threads[i - 1], NULL);
		i--;
	}
}

void	*thread_calc_projection(void *param)
{
	t_env	*env;
	int		y;
	int		x;

	env = ((t_thread_param *)param)->env;
	y = ((t_thread_param *)param)->start - 1;
	while (++y < ((t_thread_param *)param)->end)
	{
		if (y % env->points_reduction_factor == 0)
		{
			x = -1;
			while (++x < env->map->length)
				if (x % env->points_reduction_factor == 0)
					calculate_point_projection(x, y, env, ((t_thread_param *)param)->trigo_calcs);
		}
	}
	return (NULL);
}

char	*info_string(t_env *env)
{
	char	*perspective;
	size_t	last_frame_tmstp;
	double	(*local_axes)[3] = env->camera->local_axes;

	last_frame_tmstp = env->timestamp_last_frame;
	env->timestamp_last_frame = get_time();
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
			env->camera->proj_z,
			local_axes[0][0], local_axes[0][1], local_axes[0][2],
			local_axes[1][0], local_axes[1][1], local_axes[1][2],
			local_axes[2][0], local_axes[2][1], local_axes[2][2],
			env->camera->distance, env->camera->scale,
			env->camera->mouse_sensibility, env->camera->fov,
			env->camera->znear, env->camera->zfar, env->camera->right,
			env->camera->left, env->camera->top, env->camera->bottom,
			env->camera->near, env->camera->far, env->mouse_click_rotation,
			env->mouse_click_translation, env->mouse_sensibility,
			env->mouse_last_x, env->mouse_last_y, env->frames_gen,
			1.0 / ((double)(env->timestamp_last_frame - last_frame_tmstp) / 1000000.0),
			env->sphere_proj, perspective, env->z_ordering,
			!env->cam_around_focus, env->z_ratio, env->color_preset,
			env->color_preset, env->auto_point_reduc, env->points_reduction_factor));
}

char	*debug_string(t_env *env)
{
	//t_frustum *frustum = &env->camera->frustum;
	double	(*local_axes)[3] = env->camera->local_axes;
	// return (params_to_string("Frustum :\nLeft = (%f, %f, %f, %f)\nBott = (%f, %f, %f, %f)\nNear = (%f, %f, %f, %f)",
	// frustum->planes[0].a, frustum->planes[0].b, frustum->planes[0].c, frustum->planes[0].d, 
	// frustum->planes[2].a, frustum->planes[2].b, frustum->planes[2].c, frustum->planes[2].d, 
	// frustum->planes[4].a, frustum->planes[4].b, frustum->planes[4].c, frustum->planes[4].d));
	// 
	return (params_to_string("Cam local axes :\nF = (%f, %f, %f)\nU = (%f, %f, %f)\nR = (%f, %f, %f)", 
	local_axes[0][0], local_axes[0][1], local_axes[0][2], local_axes[1][0], local_axes[1][1], local_axes[1][2], local_axes[2][0], local_axes[2][1], local_axes[2][2]));
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
	if (env->debug_mode)
	{
		// text_pos.y = 540;
		// dynamic_infos = debug_string(env);
		// if (dynamic_infos)
		// 	string_to_img(env->img, env->font, text_pos, dynamic_infos);
		// free(dynamic_infos);
	}
}

void initZBuffer(float *zBuffer, size_t pixel_amount)
{	
	size_t	i;

	i = 0;
    while (i < pixel_amount)
	{
        zBuffer[i] = FLT_MAX;
		i++;
    }
}

void	display_selected_points(t_env *env)
{
	int	i;

	if (env->selected_point.x != -1)
	{
		circle_bres(
			env->point_list[env->selected_point.y * env->map->length + env->selected_point.x].x,
			env->point_list[env->selected_point.y * env->map->length + env->selected_point.x].y,
			SELECT_RANGE, env, 0xFFFFFF
		);
	}
	if (env->points_selection.is_active == 1)
	{
		i = 0;
		while (i < env->points_selection.amount_of_points)
		{
			circle_bres(
				env->point_list[env->points_selection.selected_points[i].y * env->map->length + env->points_selection.selected_points[i].x].x,
				env->point_list[env->points_selection.selected_points[i].y * env->map->length + env->points_selection.selected_points[i].x].y,
				SELECT_RANGE, env, 0xFFFFFF
			);
			i++;
		}
	}
}

void	display_painter_components(t_env *env)
{
	int	i;

	if (env->painter.is_active)
	{
		if (!(env->is_control_down && env->mouse_click_select))
		{
			if (env->painter.mode == 0)
				circle_bres(env->mouse_last_x, env->mouse_last_y, env->painter.radius, env, env->painter.color);
			else
				circle_bres(env->mouse_last_x, env->mouse_last_y, env->painter.radius, env, 0xFFFFFF);
		}
		display_slider_int(env->img, env->brush_size_slider);
		display_slider_int(env->img, env->brush_intensity_slider);
		i = 0;
		while (i < 52)
		{
			display_button(env->img, env->color_buttons[i], env->font);
			i++;
		}
		display_text_input(env->img, &env->save_input, env->font);
	}	
}

void	render_frame(t_env *env)
{
	ft_bzero(env->img->img_str, WIN_WIDTH * WIN_HEIGHT * (env->img->bits / 8));
	if (env->z_ordering)
		initZBuffer(env->img->img_depth, WIN_WIDTH * WIN_HEIGHT);
	if (env->auto_point_reduc)
		env->points_reduction_factor = 3 / (env->camera->scale) > 1 ? 3 / (env->camera->scale) : 1;
	calculate_every_projection(env);
	save_lines(env);
	draw_every_lines(env);
	display_selected_points(env);
	if (env->is_control_down && env->mouse_click_select)
		draw_rectangle(env, env->points_selection.start_mouse_x, env->points_selection.start_mouse_y, env->mouse_last_x, env->mouse_last_y);
	display_infos_win(env);
	display_painter_components(env);
	mlx_put_image_to_window(env->mlx, env->mlx_win, env->img->img, 0, 0);
	env->frames_gen += 1;
}
