/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:36:03 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/15 11:54:01 by lilefebv         ###   ########lyon.fr   */
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
	if (free_env)
		free(env);
}

void	exit_free(t_env *env)
{
	free_lns(env, 0);
	if (env->img->img)
		mlx_destroy_image(env->mlx, env->img->img);
	free(env->img);
	if (env->mlx_win)
		mlx_destroy_window(env->mlx, env->mlx_win);
	mlx_destroy_display(env->mlx);
	free(env->mlx);
	env->mlx = NULL;
	free(env);
	env = NULL;
}

int	render_next_frame(t_env *env)
{
	render_frame(env);
	return (1);
}

int	main(int argc, char **argv)
{
	t_env	*env;

	if (argc != 2)
		return (print_error("Please provide a map (fdf <mapname.fdf>)"), 1);
	env = calloc(sizeof(t_env), 1);
	if (!env)
		return (print_error("An error occured"), 1);
	if (init_all(env, argv) == 0)
		return (1);
	events(env);
	mlx_loop_hook(env->mlx, render_next_frame, env);
	mlx_loop(env->mlx);
	display_infos(env);
	exit_free(env);
	return (0);
}
