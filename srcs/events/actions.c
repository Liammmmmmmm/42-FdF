/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:26:16 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/12 14:35:00 by lilefebv         ###   ########lyon.fr   */
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
	if (keycode == 65307)
		mlx_loop_end(((t_env*)param)->mlx);
	else if (keycode == 45 && ((t_env*)param)->z_ratio > 0.01)
		((t_env*)param)->z_ratio -= 0.1;
	else if (keycode == 61)
		((t_env*)param)->z_ratio += 0.1;
	else if (keycode == 112)
		((t_env*)param)->perspective = 1;
	else if (keycode == 111)
		((t_env*)param)->perspective = 0;
	else if (keycode == 108)
		((t_env*)param)->perspective = 2;
	else if (keycode == 102)
		((t_env*)param)->cam_around_focus = flip_flop(((t_env*)param)->cam_around_focus);
	else if (keycode == 122)
		((t_env*)param)->z_ordering = flip_flop(((t_env*)param)->z_ordering);
	else if (keycode == 113)
		roll(-1, (t_env*)param);
	else if (keycode == 101)
		roll(1, (t_env*)param);
	else if (keycode == 99)
	{
		if (((t_env*)param)->display_infos == 2)
			((t_env*)param)->display_infos = 0;
		else
			((t_env*)param)->display_infos = 2;
	}
	else if (keycode == 105)
	{
		if (((t_env*)param)->display_infos == 1)
			((t_env*)param)->display_infos = 0;
		else
			((t_env*)param)->display_infos = 1;
	}
	return (0);
}
