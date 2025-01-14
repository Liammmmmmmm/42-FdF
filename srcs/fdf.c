/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:36:03 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/14 11:40:55 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	exit_free(t_env *env)
{
	display_infos(env);
	free(env->point_list);
	free(env->lines);
	ft_free_tab_int(env->map->map, env->map->height);
	ft_free_tab_int(env->map->color_map, env->map->height);
	free(env->map);
	free(env->camera);
	mlx_destroy_image(env->mlx, env->img->img);
	free(env->img);
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

	env = calloc(sizeof(t_env), 1);
	if (!env)
		return (print_error("An error occured"), 1);
	if (argc != 2)
		return (print_error("No map provided"), 1);
	if (init_all(env, argv) == 0)
		return (1);
	events(env);
	mlx_loop_hook(env->mlx, render_next_frame, env);
	mlx_loop(env->mlx);
	exit_free(env);
	return (0);
}
