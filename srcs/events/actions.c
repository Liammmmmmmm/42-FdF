/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:26:16 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/13 14:24:37 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	mouse_down(int button, int x, int y, void *param)
{
	((t_env*)param)->mouse_last_x = x;
	((t_env*)param)->mouse_last_y = y;
	if (button == SCROLL_DOWN || button == SCROLL_UP)
		zoom(param, button);
	else if (button == LEFT_CLICK || button == RIGHT_CLICK)
		((t_env*)param)->mouse_click_rotation = 1;
	else if (button == MIDDLE_CLICK)
		((t_env*)param)->mouse_click_translation = 1;
	return (0);
}

int	mouse_up(int button, int x, int y, void *param)
{
	((t_env*)param)->mouse_last_x = x;
	((t_env*)param)->mouse_last_y = y;
	if (button == LEFT_CLICK || button == RIGHT_CLICK)
		((t_env*)param)->mouse_click_rotation = 0;
	else if (button == MIDDLE_CLICK)
		((t_env*)param)->mouse_click_translation = 0;
	return (0);
}

int	mouse_move(int x, int y, void *param)
{
	if (((t_env*)param)->mouse_click_rotation)
		rotate(x, y, (t_env*)param);
	if (((t_env*)param)->mouse_click_translation)
		translate(x, y, (t_env*)param);
	((t_env*)param)->mouse_last_x = x;
	((t_env*)param)->mouse_last_y = y;
	return (0);
}

int	destroy(void *param)
{
	if (param != NULL)
		mlx_loop_end(((t_env*)param)->mlx);
	return (0);
}

int	keydown(int keycode, void *param)
{
	ft_printf("%d\n", keycode);
	if (keycode == KEY_ESC)
		mlx_loop_end(((t_env*)param)->mlx);
	else if (keycode == KEY_MINUS && ((t_env*)param)->z_ratio > 0.01)
		((t_env*)param)->z_ratio -= 0.1;
	else if (keycode == KEY_PLUS)
		((t_env*)param)->z_ratio += 0.1;
	else if (keycode == KEY_P)
		((t_env*)param)->perspective = 1;
	else if (keycode == KEY_O)
		((t_env*)param)->perspective = 0;
	else if (keycode == KEY_L)
		((t_env*)param)->perspective = 2;
	else if (keycode == KEY_F)
		((t_env*)param)->cam_around_focus = flip_flop(((t_env*)param)->cam_around_focus);
	else if (keycode == KEY_Z)
		((t_env*)param)->z_ordering = flip_flop(((t_env*)param)->z_ordering);
	else if (keycode == KEY_Q)
		roll(-1, (t_env*)param);
	else if (keycode == KEY_E)
		roll(1, (t_env*)param);
	else if (keycode == KEY_C)
	{
		if (((t_env*)param)->display_infos == 2)
			((t_env*)param)->display_infos = 0;
		else
			((t_env*)param)->display_infos = 2;
	}
	else if (keycode == KEY_I)
	{
		if (((t_env*)param)->display_infos == 1)
			((t_env*)param)->display_infos = 0;
		else
			((t_env*)param)->display_infos = 1;
	}
	else if (keycode == KEY_INF && ((t_env*)param)->camera->fov > 30)
		((t_env*)param)->camera->fov -= 1;
	else if (keycode == KEY_SUP && ((t_env*)param)->camera->fov < 120)
		((t_env*)param)->camera->fov += 1;
	else if (keycode == KEY_W || keycode == KEY_A || keycode == KEY_S || keycode == KEY_D || keycode == KEY_SHIFT || keycode == KEY_SPACE)
		wasd_move(keycode, (t_env*)param);
	return (0);
}
