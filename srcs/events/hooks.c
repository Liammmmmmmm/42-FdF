/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:25:37 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/14 11:05:57 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	keydown(int keycode, void *param)
{
	t_env	*env;

	env = (t_env *)param;
	if (keycode == KEY_ESC)
		mlx_loop_end(env->mlx);
	else if (keycode == KEY_MINUS && env->z_ratio > 0.01)
		env->z_ratio -= 0.1;
	else if (keycode == KEY_PLUS)
		env->z_ratio += 0.1;
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
	else if (keycode == KEY_G)
		env->color_by_height = flip_flop(env->color_by_height);
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
