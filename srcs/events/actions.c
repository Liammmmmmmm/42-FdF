/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:26:16 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/06 15:45:55 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_every_buttons(t_env *env)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		if (button_action(env->color_buttons[i], env->mouse_last_x, env->mouse_last_y) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	mouse_down(int button, int x, int y, void *param)
{
	((t_env *)param)->mouse_last_x = x;
	((t_env *)param)->mouse_last_y = y;
	if (button == SCROLL_DOWN || button == SCROLL_UP)
		zoom(param, button);
	else if (button == LEFT_CLICK)
	{
		if(check_every_buttons((t_env *)param) == 1)
			return (0);
		((t_env *)param)->mouse_click_rotation = 1;
	}
	else if (button == RIGHT_CLICK)
	{
		((t_env *)param)->mouse_click_select = 1;
		save_point_at_mouse((t_env *)param);
	}
	else if (button == MIDDLE_CLICK)
		((t_env *)param)->mouse_click_translation = 1;
	return (0);
}

int	mouse_up(int button, int x, int y, void *param)
{
	((t_env *)param)->mouse_last_x = x;
	((t_env *)param)->mouse_last_y = y;
	if (button == LEFT_CLICK)
		((t_env *)param)->mouse_click_rotation = 0;
	else if (button == RIGHT_CLICK)
	{
		((t_env *)param)->mouse_click_select = 0;
		if (((t_env *)param)->is_control_down)
			mouse_up_select((t_env *)param);
	}
	else if (button == MIDDLE_CLICK)
		((t_env *)param)->mouse_click_translation = 0;

	return (0);
}

int	mouse_move(int x, int y, void *param)
{
	if (((t_env *)param)->mouse_click_rotation)
		rotate(x, y, (t_env *)param);
	if (((t_env *)param)->mouse_click_translation)
		translate(x, y, (t_env *)param);
	((t_env *)param)->mouse_last_x = x;
	((t_env *)param)->mouse_last_y = y;
	return (0);
}

int	destroy(void *param)
{
	if (param != NULL)
		mlx_loop_end(((t_env *)param)->mlx);
	return (0);
}

void	cam_keys(int keycode, t_env *env)
{
	if (keycode == KEY_W || keycode == KEY_A || keycode == KEY_S
		|| keycode == KEY_D || keycode == KEY_SHIFT || keycode == KEY_SPACE)
		wasd_move(keycode, env);
	else if (keycode == KEY_Q)
		roll(-1, env);
	else if (keycode == KEY_E)
		roll(1, env);
	else if (keycode == KEY_INF && env->camera->fov > 30)
		env->camera->fov -= 1;
	else if (keycode == KEY_SUP && env->camera->fov < 120)
		env->camera->fov += 1;
	else if (keycode == KEY_P)
		env->perspective = 1;
	else if (keycode == KEY_O)
		env->sphere_proj = flip_flop(env->sphere_proj);
	else if (keycode == KEY_L)
		env->perspective = 2;
	else if (keycode == KEY_F)
		env->cam_around_focus = flip_flop(env->cam_around_focus);
}
