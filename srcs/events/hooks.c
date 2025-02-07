/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:25:37 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/07 16:03:30 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_z_ratio(int key, t_env *env)
{
	if (key == KEY_MINUS)
	{
		if (env->z_ratio > (double)0.14)
			env->z_ratio -= 0.1;
		else if (env->z_ratio > (double)0)
			env->z_ratio -= 0.02;
		if (env->z_ratio < 0)
			env->z_ratio = 0;
	}
	else if (key == KEY_PLUS)
	{
		if (env->z_ratio > (double)0.14)
			env->z_ratio += 0.1;
		else
			env->z_ratio += 0.02;
	}
}

void	set_color_preset(int key, t_env *env)
{
	if (key == NUM_0)
		env->color_preset = 0;
	else if (key == NUM_1)
		env->color_preset = 1;
	else if (key == NUM_2)
		env->color_preset = 2;
	else if (key == NUM_3)
		env->color_preset = 3;
	else if (key == NUM_4)
		env->color_preset = 4;
	else if (key == NUM_5)
		env->color_preset = 5;
	else if (key == NUM_6)
		env->color_preset = 6;
	else if (key == NUM_7)
		env->color_preset = 7;
	else if (key == NUM_8)
		env->color_preset = 8;
}

int	keydown(int key, void *param)
{
	t_env	*env;

	env = (t_env *)param;
	if (key == KEY_ESC)
		mlx_loop_end(env->mlx);
	else if (text_input_type(&env->save_input, key))
		return (0);
	else if (key == KEY_MINUS || key == KEY_PLUS)
		change_z_ratio(key, env);
	else if (key == KEY_Z)
		env->z_ordering = flip_flop(env->z_ordering);
	else if (key == KEY_C && env->display_infos == 2)
		env->display_infos = 0;
	else if (key == KEY_C && env->display_infos != 2)
		env->display_infos = 2;
	else if (key == KEY_I && env->display_infos == 1)
		env->display_infos = 0;
	else if (key == KEY_I && env->display_infos != 1)
		env->display_infos = 1;
	else if (key == KEY_J && env->points_reduction_factor > 1)
	{
		env->points_reduction_factor -= 1;
		if (env->points_selection.is_active)
		{
			free(env->points_selection.selected_points);
			env->points_selection.is_active = 0;
		}
	}
	else if (key == KEY_K)
	{
		env->points_reduction_factor += 1;
		if (env->points_selection.is_active)
		{
			free(env->points_selection.selected_points);
			env->points_selection.is_active = 0;
		}
	}
	else if (key == KEY_G)
		env->custom_color = flip_flop(env->custom_color);
	else if (key == KEY_H)
		env->auto_point_reduc = flip_flop(env->auto_point_reduc);
	else if (key == KEY_T)
	{
		env->painter.is_active = flip_flop(env->painter.is_active);
		if (env->points_selection.is_active)
		{
			free(env->points_selection.selected_points);
			env->points_selection.is_active = 0;
		}
	}
	else if (key == KEY_X)
		env->line_algo = sitch_mode(env->line_algo, 2);
	else if (key == KEY_B || key == KEY_N || key == KEY_V)
		edit_point(key, env);
	else if (key == KEY_CTRL_LEFT)
		env->is_control_down = 1;
	else if (key == KEY_R)
		save_map("test.fdf", env);
	else if (key == NUM_0 || key == NUM_1 || key == NUM_2 || key == NUM_3 || key == NUM_4 || key == NUM_5 || key == NUM_6 || key == NUM_7 || key == NUM_8)
		set_color_preset(key, env);
	cam_keys(key, env);
	return (0);
}

int	keyup(int key, void *param)
{
	t_env	*env;

	env = (t_env *)param;
	if (key == KEY_CTRL_LEFT)
		env->is_control_down = 0;
	return (0);
}

void	events(t_env *env)
{
	mlx_hook(env->mlx_win, ON_MOUSEDOWN, 1L << 2, mouse_down, env);
	mlx_hook(env->mlx_win, ON_MOUSEUP, 1L << 3, mouse_up, env);
	mlx_hook(env->mlx_win, ON_MOUSEMOVE, 1L << 6, mouse_move, env);
	mlx_hook(env->mlx_win, ON_DESTROY, 0, destroy, env);
	mlx_hook(env->mlx_win, ON_KEYDOWN, 1L << 0, keydown, env);
	mlx_hook(env->mlx_win, ON_KEYUP, 1L << 1, keyup, env);
}
