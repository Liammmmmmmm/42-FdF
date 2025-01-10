/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:36:03 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/09 13:38:06 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_map(t_map *map)
{
	ft_printf("map en %dx%d (lxh)\n", map->length, map->height);
	int i = 0;
	while (i < map->height)
	{
		int y = 0;
		while (y < map->length)
		{
			ft_printf("%d,%x ", map->map[i][y], map->color_map[i][y]);
			y++;
		}
		i++;
		ft_printf("\n");
	}
}

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
	//t_camera *camera = env->camera;
//	ft_printf("%p\n", &env->camera->y);
	// ft_printf("distance : %d | focus : x:%d, y:%d, z:%d | proj x:%d, y:%d, z:%d | pitch:%d, yaw:%d, roll:%d\n", camera->distance, camera->x, camera->y, camera->z, camera->proj_x, camera->proj_y, camera->proj_z, camera->pitch, camera->yaw, camera->roll);
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
