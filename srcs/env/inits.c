/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:34:24 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/15 14:55:01 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	init_camera(t_env *env)
{
	env->camera = malloc(sizeof(t_camera));
	if (!env->camera)
		return (0);
	env->camera->x = env->map->length / 2;
	env->camera->y = env->map->height / 2;
	env->camera->z = 0;
	env->camera->yaw = -PI_10D / 4.0;
	env->camera->pitch = atan(sqrt(2.0));
	env->camera->roll = 0.0;
	env->camera->distance = sqrt(env->map->length + env->map->height) + 5;
	env->camera->mouse_sensibility = env->mouse_sensibility
		/ env->camera->distance;
	env->camera->scale = calc_scale(env->map, env->camera);
	env->camera->fov = 60;
	env->camera->zfar = 100000;
	env->camera->znear = 1;
	env->camera->right = env->map->length;
	env->camera->left = 0;
	env->camera->top = 100;
	env->camera->bottom = 0;
	env->camera->far = env->map->height;
	env->camera->near = 0;
	calc_cam_proj(env, env->camera);
	return (1);
}

int	init_points(t_env *env)
{
	env->point_list
		= malloc(sizeof(t_point) * env->map->length * env->map->height);
	if (!env->point_list)
		return (0);
	return (1);
}

int	init_lines(t_env *env)
{
	int	max_lines;

	max_lines = (env->map->height - 1) * env->map->length
		+ (env->map->length - 1) * env->map->height;
	env->lines = malloc(sizeof(t_line) * max_lines);
	if (!env->lines)
		return (0);
	return (1);
}

void	random_values_init(t_env *env)
{
	env->mouse_sensibility = 0.4;
	env->z_ratio = 1;
	env->cam_around_focus = 1;
	env->perspective = 1;
	env->z_ordering = 0;
	env->frames_gen = 0;
	init_font(env);
	env->display_infos = 2;
	if (get_biggest(env->map->height, env->map->length) < env->map->highest)
		env->z_ratio = (double)get_biggest(env->map->height, env->map->length)
			/ env->map->highest;
	env->color_by_height = !env->map->have_color;
}

int	init_all(t_env *env, char **argv)
{
	env->map = parse_map(argv[1]);
	if (!env->map)
		return (print_error("Map initialization failed"), free(env), 0);
	random_values_init(env);
	if (init_camera(env) == 0)
		return (print_error("Camera initialization failed"), fr_map(env, 1), 0);
	if (init_points(env) == 0)
		return (print_error("Points initialization failed"), fr_cam(env, 1), 0);
	if (init_lines(env) == 0)
		return (print_error("Lines initialization failed"), fr_pts(env, 1), 0);
	env->img = malloc(sizeof(t_img));
	if (!env->img)
		return (print_error("initialization init failed"), free_lns(env, 1), 0);
	env->mlx = mlx_init();
	if (!env->mlx)
		return (print_error(ERROR_MLX), free(env->img), free_lns(env, 1), 0);
	env->mlx_win = mlx_new_window(env->mlx, WIN_WIDTH, WIN_HEIGHT, "FdF");
	env->img->img = mlx_new_image(env->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!env->mlx_win || !env->img->img)
		return (print_error("An error occured"), exit_free(env), 0);
	env->img->img_str = mlx_get_data_addr(env->img->img, &env->img->bits,
			&env->img->size_line, &env->img->endian);
	if (!env->img->img_str)
		return (print_error("An error occured"), exit_free(env), 0);
	return (1);
}
