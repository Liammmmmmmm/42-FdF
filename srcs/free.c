/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:05:37 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/04 17:45:18 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fr_map(t_env *env, int free_env)
{
	ft_free_tab_int(env->map->map, env->map->height);
	ft_free_tab_int(env->map->color_map, env->map->height);
	free(env->map);
	if (free_env)
		free(env);
}

void	fr_cam(t_env *env, int free_env)
{
	fr_map(env, 0);
	free(env->camera);
	if (free_env)
		free(env);
}

void	fr_pts(t_env *env, int free_env)
{
	fr_cam(env, 0);
	free(env->point_list);
	if (free_env)
		free(env);
}

void	free_lns(t_env *env, int free_env)
{
	fr_pts(env, 0);
	free(env->lines);
	free(env->threads);
	free(env->threads_params);
	if (free_env)
	{
		free(env->img);
		free(env);
	}
}

void	exit_free(t_env *env)
{
	free_lns(env, 0);
	if (env->img->img)
		mlx_destroy_image(env->mlx, env->img->img);
	free(env->img->img_depth);
	if (env->img->is_mutex_ok)
		pthread_mutex_destroy(&env->img->img_mutex);
	free(env->img);
	if (env->mlx_win)
		mlx_destroy_window(env->mlx, env->mlx_win);
	mlx_destroy_display(env->mlx);
	free(env->mlx);
	env->mlx = NULL;
	free(env);
	env = NULL;
}
