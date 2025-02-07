/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:25:42 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/07 12:43:10 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	paint_color(t_env *env)
{
	size_t		point_amount;
	size_t		i;
	int			dx;
	int			dy;
	int			distance;

	point_amount = env->map->height * env->map->length;
	i = 0;
	while (i < point_amount)
	{
		dx = env->point_list[i].x - env->mouse_last_x;
        dy = env->point_list[i].y - env->mouse_last_y;
        distance = sqrt(dx * dx + dy * dy);
		if (distance <= env->painter.radius)
		{
			if ((i % env->map->length) % env->points_reduction_factor == 0
				&& (i / env->map->length) % env->points_reduction_factor == 0
				&& env->map->edited[i] == 0)
			{
				env->map->edited[i] = 1;
				env->map->color_map[i / env->map->length][i % env->map->length] = calc_gradiant_color(env->map->color_map[i / env->map->length][i % env->map->length], env->painter.color, (double)env->painter.intensity / 100);
			}
		}
		i++;	
	}
}

void	up_point(t_env *env)
{
	size_t		point_amount;
	size_t		i;
	int			dx;
	int			dy;
	int			distance;

	point_amount = env->map->height * env->map->length;
	i = 0;
	while (i < point_amount)
	{
		dx = env->point_list[i].x - env->mouse_last_x;
        dy = env->point_list[i].y - env->mouse_last_y;
        distance = sqrt(dx * dx + dy * dy);
		if (distance <= env->painter.radius)
		{
			if ((i % env->map->length) % env->points_reduction_factor == 0
				&& (i / env->map->length) % env->points_reduction_factor == 0
				&& env->map->edited[i] == 0)
			{
				env->map->edited[i] = 1;
				env->map->map[i / env->map->length][i % env->map->length] += env->painter.intensity / 10;
			}
		}
		i++;	
	}
}

void	down_point(t_env *env)
{
	size_t		point_amount;
	size_t		i;
	int			dx;
	int			dy;
	int			distance;

	point_amount = env->map->height * env->map->length;
	i = 0;
	while (i < point_amount)
	{
		dx = env->point_list[i].x - env->mouse_last_x;
        dy = env->point_list[i].y - env->mouse_last_y;
        distance = sqrt(dx * dx + dy * dy);
		if (distance <= env->painter.radius)
		{
			if ((i % env->map->length) % env->points_reduction_factor == 0
				&& (i / env->map->length) % env->points_reduction_factor == 0
				&& env->map->edited[i] == 0)
			{
				env->map->edited[i] = 1;
				env->map->map[i / env->map->length][i % env->map->length] -= env->painter.intensity / 10;
			}
		}
		i++;	
	}
}

void	flattern_point(t_env *env)
{
	size_t		point_amount;
	size_t		i;
	int			dx;
	int			dy;
	int			distance;

	point_amount = env->map->height * env->map->length;
	i = 0;
	while (i < point_amount)
	{
		dx = env->point_list[i].x - env->mouse_last_x;
        dy = env->point_list[i].y - env->mouse_last_y;
        distance = sqrt(dx * dx + dy * dy);
		if (distance <= env->painter.radius)
		{
			if ((i % env->map->length) % env->points_reduction_factor == 0
				&& (i / env->map->length) % env->points_reduction_factor == 0
				&& env->map->edited[i] == 0)
			{
				env->map->edited[i] = 1;
				env->map->map[i / env->map->length][i % env->map->length] = 0 + env->map->map[i / env->map->length][i % env->map->length] * (1 - (double)env->painter.intensity / 100);
			}
		}
		i++;	
	}
}

void	paint_area(t_env *env, int x, int y)
{
	static int last_x = -1;
	static int last_y = -1;
	
	if (x == -1 && y == -1)
	{
		last_x = -1;
		last_y = -1;
		return ;
	}

	if (env->painter.is_active == 0 || env->mouse_click_select == 0 || env->is_control_down || (last_x == env->mouse_last_x && last_y == env->mouse_last_y))
		return ;
	if (env->painter.mode == 0)
		paint_color(env);
	else if (env->painter.mode == 1)
		up_point(env);
	else if (env->painter.mode == 2)
		down_point(env);
	else if (env->painter.mode == 3)
		flattern_point(env);
	last_x = env->mouse_last_x;
	last_y = env->mouse_last_y;
}

void	change_brush_color(void *color)
{
	((t_brush_c *)color)->env->painter.color = ((t_brush_c *)color)->color;
	((t_brush_c *)color)->env->painter.mode = 0;
}

void	change_brush_mode(void *color)
{
	((t_brush_c *)color)->env->painter.mode = ((t_brush_c *)color)->color;
}
