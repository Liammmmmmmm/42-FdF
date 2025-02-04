/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:25:37 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/04 11:34:48 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_z_ratio(int keycode, t_env *env)
{
	if (keycode == KEY_MINUS)
	{
		if (env->z_ratio > (double)0.14)
			env->z_ratio -= 0.1;
		else if (env->z_ratio > (double)0)
			env->z_ratio -= 0.02;
		if (env->z_ratio < 0)
			env->z_ratio = 0;
	}
	else if (keycode == KEY_PLUS)
	{
		if (env->z_ratio > (double)0.14)
			env->z_ratio += 0.1;
		else
			env->z_ratio += 0.02;
	}
}

void	set_color_preset(int keycode, t_env *env)
{
	if (keycode == NUM_0)
		env->color_preset = 0;
	else if (keycode == NUM_1)
		env->color_preset = 1;
	else if (keycode == NUM_2)
		env->color_preset = 2;
	else if (keycode == NUM_3)
		env->color_preset = 3;
	else if (keycode == NUM_4)
		env->color_preset = 4;
	else if (keycode == NUM_5)
		env->color_preset = 5;
	else if (keycode == NUM_6)
		env->color_preset = 6;
	else if (keycode == NUM_7)
		env->color_preset = 7;
	else if (keycode == NUM_8)
		env->color_preset = 8;
}

int	keydown(int keycode, void *param)
{
	t_env	*env;

	env = (t_env *)param;
	if (keycode == KEY_ESC)
		mlx_loop_end(env->mlx);
	else if (keycode == KEY_MINUS || keycode == KEY_PLUS)
		change_z_ratio(keycode, env);
	else if (keycode == KEY_Z)
		env->z_ordering = flip_flop(env->z_ordering);
	else if (keycode == KEY_C && env->display_infos == 2)
		env->display_infos = 0;
	else if (keycode == KEY_C && env->display_infos != 2)
		env->display_infos = 2;
	else if (keycode == KEY_I && env->display_infos == 1)
		env->display_infos = 0;
	else if (keycode == KEY_I && env->display_infos != 1)
		env->display_infos = 1;
	else if (keycode == KEY_J && env->points_reduction_factor > 1)
		env->points_reduction_factor -= 1;
	else if (keycode == KEY_K)
		env->points_reduction_factor += 1;
	else if (keycode == KEY_G)
		env->custom_color = flip_flop(env->custom_color);
	else if (keycode == NUM_0 || keycode == NUM_1 || keycode == NUM_2
		|| keycode == NUM_3 || keycode == NUM_4 || keycode == NUM_5
		|| keycode == NUM_6 || keycode == NUM_7 || keycode == NUM_8)
		set_color_preset(keycode, env);
	cam_keys(keycode, env);
	return (0);
}

void	events(t_env *env)
{
	mlx_hook(env->mlx_win, ON_MOUSEDOWN, 1L << 2, mouse_down, env);
	mlx_hook(env->mlx_win, ON_MOUSEUP, 1L << 3, mouse_up, env);
	mlx_hook(env->mlx_win, ON_MOUSEMOVE, 1L << 6, mouse_move, env);
	mlx_hook(env->mlx_win, ON_DESTROY, 0, destroy, env);
	mlx_hook(env->mlx_win, ON_KEYDOWN, 1L << 0, keydown, env);
}
