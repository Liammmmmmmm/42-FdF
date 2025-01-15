/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:36:03 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/15 14:50:08 by lilefebv         ###   ########lyon.fr   */
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
	if (env->map->highest == 0)
		env->map->highest = 1;
	events(env);
	mlx_loop_hook(env->mlx, render_next_frame, env);
	mlx_loop(env->mlx);
	display_infos(env);
	exit_free(env);
	return (0);
}
