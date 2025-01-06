/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:36:03 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/06 18:51:00 by lilefebv         ###   ########lyon.fr   */
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

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	x += 1920 / 2;
	y += 1080 / 2;
	if (x >= 0 && x < 1920 && y >= 0 && y < 1080)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

t_data	create_frame(t_env *env)
{
	t_data		img;

	img.img = mlx_new_image(env->mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	int y = 0;
	while (y < env->map->height)
	{
		int x = 0;
		while (x < env->map->length)
		{
			t_point *point = calculate_point_projection(x, y, env->map, env->camera);
			my_mlx_pixel_put(&img, point->x, point->y, point->color);
			free(point);
			x++;
		}
		y++;
	}
	return (img);
}

double calc_scale(t_map *map, t_camera *camera)
{
    double screen_size = 1920.0;
    double depth_factor = camera->distance / 10.0;
    double scale = screen_size / depth_factor;
    double map_size = fmax(map->length, map->height);
	
    scale /= map_size;

    return scale;
}

t_camera	*init_camera(t_map *map)
{
	t_camera	*camera;

	camera = malloc(sizeof(t_camera));
	if (!camera)
		return (NULL);
	camera->x = map->length / 2;
	camera->y = map->height / 2;
	camera->z = 0;
	// camera->pitch = -PI_10D / 2;
    // camera->yaw = 0.0;
    // camera->roll = 0.0;
	camera->pitch = atan(sqrt(2.0));
	camera->yaw = PI_10D / 4.0;
	camera->roll = 0.0;
	camera->distance = 30;
	camera->scale = calc_scale(map, camera);
	camera->proj_x = camera->x - camera->distance * cos(camera->pitch) * cos(camera->yaw);
	camera->proj_y = camera->y - camera->distance * cos(camera->pitch) * sin(camera->yaw);
	camera->proj_z = camera->z - camera->distance * sin(camera->pitch);
	#include <stdio.h>
	printf("x:%.6f y:%.6f z:%.6f\n", camera->proj_x, camera->proj_y, camera->proj_z);
	return (camera);
}

int	mouse_down(int button, int x, int y, void *param)
{
	
}

void	events(t_env *env)
{
	mlx_hook(env->mlx, 4, 0, mouse_down, &env);
}

int	main(int argc, char **argv)
{
	void	*mlx_win;
	t_data	img;
	t_env	*env;

	if (argc != 2)
		return (print_error("No map provided"), 1);
	env = malloc(sizeof(t_env));
	if (!env)
		return (print_error("An error occured"), 1);
	env->map = parse_map(argv[1]);
	if (!env->map)
		return (print_error("An error occured"), free(env), 1);
	env->camera = init_camera(env->camera);
	if (!env->camera)
		return (print_error("An error occured"), free(env->map), free(env), 1);
	// secure malloc
	env->mlx = mlx_init();
	mlx_win = mlx_new_window(env->mlx, 1920, 1080, "Hello world!");
	img = create_frame(env);
	mlx_put_image_to_window(env->mlx, mlx_win, img.img, 0, 0);
	events(env);
	mlx_loop(env->mlx);
	return (free(env->map), free(env->camera), free(env), 0);
}
