/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:08:34 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/09 15:28:14 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_point *point_a, t_point *point_b, t_env *env)
{
	int	dx;
	int	dy;
	float	m;
	int temp;

	dx = point_b->x - point_a->x;
	dy = point_b->y - point_a->y;
	if (abs(dy) <= abs(dx))
	{
		if (dx == 0)
			return ;
		m = (float)dy / dx;
		if (point_b->x > point_a->x)
		{
			temp = point_a->x - 1;
			while (++temp <= point_b->x)
				put_pixel_image(env->img->img_str, temp, m * (temp - point_a->x) + point_a->y, calc_gradiant_color(point_a, point_b, (double)(temp - point_a->x) / dx));
		}
		else
		{
			temp = point_b->x - 1;
			while (++temp <= point_a->x)
				put_pixel_image(env->img->img_str, temp, m * (temp - point_b->x) + point_b->y, calc_gradiant_color(point_b, point_a, (1 - (double)(temp - point_b->x) / dx)));
		}
	}
	else
	{
		if (dy == 0)
			return ;
		m = (float)dx / dy;
		if (point_b->y > point_a->y)
		{
			temp = point_a->y - 1;
			while (++temp <= point_b->y)
				put_pixel_image(env->img->img_str, m * (temp - point_a->y) + point_a->x, temp, calc_gradiant_color(point_a, point_b, (double)(temp - point_a->y) / dy));
		}
		else
		{
			temp = point_b->y - 1;
			while (++temp <= point_a->y)
				put_pixel_image(env->img->img_str, m * (temp - point_b->y) + point_b->x, temp, calc_gradiant_color(point_b, point_a, (1 - (double)(temp - point_b->y) / dy)));
		}
	}
}

void	draw_every_lines(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->line_amount)
		draw_line(env->lines[i].start, env->lines[i].end, env);
}

void	save_line(t_env *env, t_point *point_a, t_point *point_b, int i)
{
	env->lines[i].start = point_a;
	env->lines[i].end = point_b;
	env->lines[i].depth = (point_a->z + point_b->z) / 2;
}

void	save_lines(t_env *env)
{
	int	y;
	int	x;
	int	i;

	i = 0;
	y = -1;
	while (++y < env->map->height)
	{
		x = -1;
		while (++x < env->map->length)
		{
			if (x < env->map->length - 1 && (is_point_in_frame(env->point_list[y * env->map->length + x]) || is_point_in_frame(env->point_list[y * env->map->length + x + 1])))
				save_line(env, &env->point_list[y * env->map->length + x], &env->point_list[y * env->map->length + x + 1], i++);
			if (y < env->map->height - 1 && (is_point_in_frame(env->point_list[y * env->map->length + x]) || is_point_in_frame(env->point_list[(y + 1) * env->map->length + x])))
				save_line(env, &env->point_list[y * env->map->length + x], &env->point_list[(y + 1) * env->map->length + x], i++);
		}
	}
	env->line_amount = i;
}

void	swap_lines(t_line *a, t_line *b)
{
	t_line temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	partition(t_line *lines, int low, int high)
{
    float	pivot;
    int		i;
	int		j;

	pivot = lines[high].depth;
	i = (low - 1);
	j = low;
	while (j < high)
	{
		if (lines[j].depth < pivot)
		{
			i++;
			swap_lines(&lines[i], &lines[j]);
		}
		j++;
	}
	swap_lines(&lines[i + 1], &lines[high]);
	return (i + 1);
}

void	quicksort_lines(t_line *lines, int low, int high)
{
	int	pi;

	if (low < high)
	{
		pi = partition(lines, low, high);
		quicksort_lines(lines, low, pi - 1);
		quicksort_lines(lines, pi + 1, high);
    }
}