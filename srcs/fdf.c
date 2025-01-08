/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:36:03 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/08 18:54:39 by lilefebv         ###   ########lyon.fr   */
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

void	ft_free_tab_points(t_point **tab, size_t i)
{
	size_t	c;

	c = 0;
	while (c < i)
	{
		free(tab[c]);
		c++;
	}
	free(tab);
}

void	exit_free(t_env *env)
{
	display_infos(env);
	ft_free_tab_points(env->point_list, env->map->length * env->map->height);
	ft_free_tab_int(env->map->map, env->map->height);
	ft_free_tab_int(env->map->color_map, env->map->height);
	free(env->map);
	env->map = NULL;
	free(env->camera);
	env->camera = NULL;
	mlx_destroy_image(env->mlx, env->img->img);
	env->img->img = NULL;
	free(env->img);
	mlx_destroy_window(env->mlx, env->mlx_win);
	env->mlx_win = NULL;
	mlx_destroy_display(env->mlx);
	free(env->mlx);
	env->mlx = NULL;
	free(env->lines);
	free(env);
	env = NULL;
}

double calc_scale(t_map *map, t_camera *camera)
{
	double depth_factor = camera->distance / 10.0;
	double scale = WIN_WIDTH / depth_factor;
	double map_size = fmax(map->length, map->height);
	
	scale /= map_size;

	return scale;
}

void	calc_cam_proj(t_camera *camera)
{
	camera->proj_x = camera->x + camera->distance * cos(camera->pitch) * cos(camera->yaw);
	camera->proj_y = camera->y + camera->distance * cos(camera->pitch) * sin(camera->yaw);
	camera->proj_z = camera->z - camera->distance * sin(camera->pitch);
}

t_camera	*init_camera(t_env *env)
{
	t_camera	*camera;

	camera = malloc(sizeof(t_camera));
	if (!camera)
		return (NULL);
	camera->x = env->map->length / 2;
	camera->y = env->map->height / 2;
	camera->z = 0;
	// camera->pitch = -PI_10D / 2;
	// camera->yaw = 0.0;
	// camera->roll = 0.0;
	camera->pitch = atan(sqrt(2.0));
	camera->yaw = PI_10D / 4.0;
	camera->roll = 0.0;
	camera->distance = camera->distance = sqrt(pow(env->map->length, 2) + pow(env->map->height, 2)) / 2.0;
	camera->mouse_sensibility = env->mouse_sensibility / camera->distance;
	camera->scale = calc_scale(env->map, camera);
	calc_cam_proj(camera);
	return (camera);
}

void	change_camera_distance(t_env *env, double new_distance)
{
	env->camera->distance = new_distance;
	env->camera->scale = calc_scale(env->map, env->camera);
	calc_cam_proj(env->camera);
	env->camera->mouse_sensibility = env->mouse_sensibility / env->camera->distance;
}

void	zoom(t_env *env, int direction)
{
	if (direction == SCROLL_UP && env->camera->distance > 0)
	{
		if (env->camera->distance <= 1)
			change_camera_distance(env, env->camera->distance - 0.1);
		else
			change_camera_distance(env, env->camera->distance - 1.0);
	}
	else if (direction == SCROLL_DOWN)
	{
		if (env->camera->distance < 1)
			change_camera_distance(env, env->camera->distance + 0.1);
		else
			change_camera_distance(env, env->camera->distance + 1.0);
	}
}

int	mouse_down(int button, int x, int y, void *param)
{
	((t_env*)param)->mouse_last_x = x;
	((t_env*)param)->mouse_last_y = y;
	if (button == SCROLL_DOWN || button == SCROLL_UP)
		zoom(param, button);
	else if (button == LEFT_CLICK || button == RIGHT_CLICK)
		((t_env*)param)->mouse_click_rotation = 1;
	else if (button == MIDDLE_CLICK)
		((t_env*)param)->mouse_click_translation = 1;
	return (0);
}

int	mouse_up(int button, int x, int y, void *param)
{
	((t_env*)param)->mouse_last_x = x;
	((t_env*)param)->mouse_last_y = y;
	if (button == LEFT_CLICK || button == RIGHT_CLICK)
		((t_env*)param)->mouse_click_rotation = 0;
	else if (button == MIDDLE_CLICK)
		((t_env*)param)->mouse_click_translation = 0;
	return (0);
}

void	rotate(int x, int y, t_env *env)
{
	int	dx;
	int	dy;

	dx = x - env->mouse_last_x;
	dy = y - env->mouse_last_y;
	env->camera->yaw += dx * env->camera->mouse_sensibility;
	env->camera->pitch += dy * env->camera->mouse_sensibility;
	if (env->camera->yaw > 2 * PI_10D)
		env->camera->yaw = 0;
	if (env->camera->yaw < 0)
		env->camera->yaw = 2 * PI_10D;
	if (env->camera->pitch > 2 * PI_10D)
		env->camera->pitch = 0;
	if (env->camera->pitch < 0)
		env->camera->pitch = 2 * PI_10D;
	calc_cam_proj(env->camera);
}

void get_local_axes(double axes[3][3], double yaw, double pitch, double roll)
{
	double	yaw_matrix[3][3];
	double	pitch_matrix[3][3];
	double	roll_matrix[3][3];
	double	temp_matrix[3][3];

    init_yaw_matrix(yaw_matrix, yaw);
    init_pitch_matrix(pitch_matrix, pitch);
    init_roll_matrix(roll_matrix, roll);
    multiply_matrix_3x3(temp_matrix, roll_matrix, pitch_matrix);
    multiply_matrix_3x3(axes, temp_matrix, yaw_matrix);
}

void	translate(int x, int y, t_env *env)
{
	int 	dx;
    int		dy;
	double	local_axes[3][3];
	double	delta_cam_move[3];

	get_local_axes(local_axes, env->camera->yaw, env->camera->pitch, env->camera->roll);
    dx = x - env->mouse_last_x;
    dy = y - env->mouse_last_y;
	delta_cam_move[0] = dx * local_axes[0][0] + dy * local_axes[1][0];
    delta_cam_move[1] = dx * local_axes[0][1] + dy * local_axes[1][1];
	delta_cam_move[2] = dx * local_axes[0][2] + dy * local_axes[1][2];
	env->camera->x += delta_cam_move[0] * env->mouse_sensibility * env->camera->distance / 100;
	env->camera->y += delta_cam_move[1] * env->mouse_sensibility * env->camera->distance / 100;
	env->camera->z += delta_cam_move[2] * env->mouse_sensibility * env->camera->distance / 100;
	calc_cam_proj(env->camera);
}

int	mouse_move(int x, int y, void *param)
{
	if (((t_env*)param)->mouse_click_rotation)
		rotate(x, y, (t_env*)param);
	if (((t_env*)param)->mouse_click_translation)
		translate(x, y, (t_env*)param);
	((t_env*)param)->mouse_last_x = x;
	((t_env*)param)->mouse_last_y = y;
	return (0);
}

int	destroy(void *param)
{
	if (param != NULL)
		mlx_loop_end(((t_env*)param)->mlx);
	return (0);
}

int	keydown(int keycode, void *param)
{
	ft_printf("%d\n", keycode);
	if (keycode == 65307)
		mlx_loop_end(((t_env*)param)->mlx);
	else if (keycode == 91 && ((t_env*)param)->z_ratio > 0)
		((t_env*)param)->z_ratio -= 0.1;
	else if (keycode == 93)
		((t_env*)param)->z_ratio += 0.1;
	else if (keycode == 105)
		display_infos((t_env*)param);
	else if (keycode == 112)
	{
		if (((t_env*)param)->perspective == 1)
			((t_env*)param)->perspective = 0;
		else
			((t_env*)param)->perspective = 1;
	}
	return (0);
}

void	events(t_env *env)
{
	mlx_hook(env->mlx_win, ON_MOUSEDOWN, 1L<<2, mouse_down, env);
	mlx_hook(env->mlx_win, ON_MOUSEUP, 1L<<3, mouse_up, env);
	mlx_hook(env->mlx_win, ON_MOUSEMOVE, 1L<<6, mouse_move, env);
	mlx_hook(env->mlx_win, ON_DESTROY, 0, destroy, env);
	mlx_hook(env->mlx_win, ON_KEYDOWN, 1L<<0, keydown, env);
}

int	init_points(t_env *env)
{
	int	y;
	int	x;

	y = 0;
	env->point_list = malloc(sizeof(t_point*) * env->map->length * env->map->height);
	if (!env->point_list)
		return (0);
	while (y < env->map->height)
	{
		x = 0;
		while (x < env->map->length)
		{
			env->point_list[y * env->map->length + x] = malloc(sizeof(t_point));
			if (!env->point_list[y * env->map->length + x])
				return (ft_free_tab_points(env->point_list, y * env->map->length + x), 0);
			x++;
		}
		y++;
	}
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

int	render_next_frame(void *env)
{
	render_frame(env);
	return (1);
}

int	main(int argc, char **argv)
{
	t_env	*env;

	if (argc != 2)
		return (print_error("No map provided"), 1);
	env = calloc(sizeof(t_env), 1);
	if (!env)
		return (print_error("An error occured"), 1);
	env->map = parse_map(argv[1]);
	if (!env->map)
		return (print_error("An error occured"), free(env), 1);
	env->camera = init_camera(env);
	if (!env->camera)
		return (print_error("An error occured"), exit_free(env), 1);
	if (init_points(env) == 0)
		return (print_error("An error occured"), exit_free(env), 1);
	if (init_lines(env) == 0)
		return (print_error("An error occured"), exit_free(env), 1);
	env->img = malloc(sizeof(t_img));
	if (!env->img)
		return (print_error("An error occured"), exit_free(env), 1);
	env->mouse_sensibility = 0.4;
	env->z_ratio = 1;
	env->perspective = 0;
	env->frames_gen = 0;
	env->mlx = mlx_init();
	env->mlx_win = mlx_new_window(env->mlx, WIN_WIDTH, WIN_HEIGHT, "FdF");
	env->img->img = mlx_new_image(env->mlx, WIN_WIDTH, WIN_HEIGHT);
	env->img->img_str = mlx_get_data_addr(env->img->img, &env->img->bits, &env->img->size_line, &env->img->endian);
	events(env);
	mlx_loop_hook(env->mlx, render_next_frame, env);
	mlx_loop(env->mlx);
	exit_free(env);
	return (0);
}
