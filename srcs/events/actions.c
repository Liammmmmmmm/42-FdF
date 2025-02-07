/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:26:16 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/07 16:14:54 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_every_buttons(t_env *env)
{
	int	i;

	i = 0;
	while (i < 52)
	{
		if (button_action(&env->color_buttons[i], env->mouse_last_x, env->mouse_last_y) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	release_every_buttons(t_env *env)
{
	int	i;

	i = 0;
	while (i < 52)
	{
		button_release(&env->color_buttons[i]);
		i++;
	}
	return (0);
}

int	mouse_down(int button, int x, int y, void *param)
{
	t_env	*env;

	env = ((t_env *)param);
	env->mouse_last_x = x;
	env->mouse_last_y = y;
	if (button == SCROLL_DOWN || button == SCROLL_UP)
	{
		if (env->painter.is_active && env->is_control_down)
		{
			if (button == SCROLL_UP)
				env->painter.radius += 2;
			else if (button == SCROLL_DOWN)
				env->painter.radius -= 2;
			if (env->painter.radius < env->brush_size_slider.min)
				env->painter.radius = env->brush_size_slider.min;
			else if (env->painter.radius > env->brush_size_slider.max)
				env->painter.radius = env->brush_size_slider.max;
		}
		else
			zoom(param, button);
	}
	else if (button == LEFT_CLICK)
	{
		if (env->painter.is_active)
		{
			if (text_input_focus(&env->save_input, x, y))
				return (0);
			if (check_every_buttons(env) == 1)
				return (0);
			if (slider_mouse_down(&env->brush_size_slider, x, y) == 1)
				return (0);
			if (slider_mouse_down(&env->brush_intensity_slider, x, y) == 1)
				return (0);
		}
		env->mouse_click_rotation = 1;
	}
	else if (button == RIGHT_CLICK)
	{
		paint_area((t_env *)param, -1, -1);
		env->mouse_click_select = 1;
		save_point_at_mouse(env);
	}
	else if (button == MIDDLE_CLICK)
		env->mouse_click_translation = 1;
	return (0);
}

int	mouse_up(int button, int x, int y, void *param)
{
	t_env	*env;

	env = ((t_env *)param);
	env->mouse_last_x = x;
	env->mouse_last_y = y;
	if (button == LEFT_CLICK)
	{ 
		if (slider_mouse_up(&env->brush_size_slider) == 1)
			return (0);
		if (slider_mouse_up(&env->brush_intensity_slider) == 1)
			return (0);
		if (env->painter.is_active)
			release_every_buttons(env);
		env->mouse_click_rotation = 0;
	}
	else if (button == RIGHT_CLICK)
	{
		env->mouse_click_select = 0;
		if (env->is_control_down)
			mouse_up_select(env);
		if (env->painter.is_active)
			ft_bzero(env->map->edited, env->map->height * env->map->length);
	}
	else if (button == MIDDLE_CLICK)
		env->mouse_click_translation = 0;

	return (0);
}

int	mouse_move(int x, int y, void *param)
{
	slider_mouse_move(&((t_env *)param)->brush_size_slider, x);
	slider_mouse_move(&((t_env *)param)->brush_intensity_slider, x);
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
