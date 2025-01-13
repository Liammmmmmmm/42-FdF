/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:34:24 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/13 15:25:53 by lilefebv         ###   ########lyon.fr   */
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
	// env->camera->pitch = 0;
	// env->camera->yaw = 0;
	// env->camera->roll = 0.0;
	env->camera->pitch = atan(sqrt(2.0));
	env->camera->yaw = -PI_10D / 4.0;
	env->camera->roll = 0.0;
	env->camera->distance = sqrt(pow(env->map->length, 2) + pow(env->map->height, 2)) / 20.0; // sqrt(pow(env->map->length, 2) + pow(env->map->height, 2)) / 2.0
	env->camera->mouse_sensibility = env->mouse_sensibility / env->camera->distance;
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
	env->point_list = malloc(sizeof(t_point) * env->map->length * env->map->height);
	if (!env->point_list)
		return (0);
	return (1);
}

int	init_lines(t_env *env)
{
	int	max_lines;

	max_lines = (env->map->height - 1) * env->map->length + (env->map->length - 1) * env->map->height;
	env->lines = malloc(sizeof(t_line) * max_lines);
	if (!env->lines)
		return (0);
	return (1);
}

// calculer un z ratio de maniere a ce que si la hauteur est plus grand que le plus grand cote on fait en sorte que le z max soit au meme niveau que le cote le plus grand

int	init_all(t_env *env, char **argv)
{
	static unsigned char font[96][5] = FONT;

	env->map = parse_map(argv[1]);
	if (!env->map)
		return (print_error("An error occured"), free(env), 0);
	if (init_camera(env) == 0)
		return (print_error("An error occured"), exit_free(env), 0);
	if (init_points(env) == 0)
		return (print_error("An error occured"), exit_free(env), 0);
	if (init_lines(env) == 0)
		return (print_error("An error occured"), exit_free(env), 0);
	env->img = malloc(sizeof(t_img));
	if (!env->img)
		return (print_error("An error occured"), exit_free(env), 0);
	env->mouse_sensibility = 0.4;
	env->z_ratio = 1;
	env->cam_around_focus = 1;
	env->perspective = 2;
	env->z_ordering = 0;
	env->frames_gen = 0;
	env->mlx = mlx_init();
	env->mlx_win = mlx_new_window(env->mlx, WIN_WIDTH, WIN_HEIGHT, "FdF");
	env->img->img = mlx_new_image(env->mlx, WIN_WIDTH, WIN_HEIGHT);
	env->img->img_str = mlx_get_data_addr(env->img->img, &env->img->bits, &env->img->size_line, &env->img->endian);
	ft_memcpy(env->font, font, sizeof(env->font));
	env->display_infos = 2;
	
	return (1);
}
