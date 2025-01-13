/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:57:10 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/13 16:34:54 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void print_camera_info(t_camera *camera)
{
	ft_printf(BOLD BLUE "[Camera Info]" NC "\n");
	ft_printf("  " GREEN "Rotation:" NC "\n");
	ft_printf("    Yaw   : " YELLOW "%f°" NC "\n", (camera->pitch * 180 / PI_10D));
	ft_printf("    Pitch : " YELLOW "%f°" NC "\n", (camera->yaw * 180 / PI_10D));
	ft_printf("    Roll  : " YELLOW "%f°" NC "\n", (camera->roll * 180 / PI_10D));
	ft_printf("  " GREEN "Position:" NC "\n");
	ft_printf("    Focus Point : " CYAN "(%f, %f, %f)" NC "\n", camera->x, camera->y, camera->z);
	ft_printf("    Real pos    : " CYAN "(%f, %f, %f)" NC "\n", camera->proj_x, camera->proj_y, camera->proj_z);
	ft_printf("  " GREEN "Parameters:" NC "\n");
	ft_printf("    Distance      : " PURPLE "%f" NC "\n", camera->distance);
	ft_printf("    Scale         : " PURPLE "%f" NC "\n", camera->scale);
	ft_printf("    Mouse Sens.   : " PURPLE "%f" NC "\n", camera->mouse_sensibility);
	ft_printf("    FOV           : " PURPLE "%d" NC "\n", camera->fov);
	ft_printf("    Near Clip     : " PURPLE "%d" NC "\n", camera->znear);
	ft_printf("    Far Clip      : " PURPLE "%d" NC "\n", camera->zfar);
	ft_printf("    Right/Left    : " CYAN "%f" NC " / " CYAN "%f" NC "\n", camera->right, camera->left);
	ft_printf("    Top/Bottom    : " CYAN "%f" NC " / " CYAN "%f" NC "\n", camera->top, camera->bottom);
	ft_printf("    Near/Far Plane: " CYAN "%f" NC " / " CYAN "%f" NC "\n", camera->near, camera->far);
	ft_printf("\n");
}

void print_map_info(t_map *map)
{
	ft_printf(BOLD BLUE "[Map Info]" NC "\n");
	ft_printf("  " GREEN "Dimensions:" NC "\n");
	ft_printf("    Length : " YELLOW "%d" NC "\n", map->length);
	ft_printf("    Height : " YELLOW "%d" NC "\n", map->height);
	ft_printf("\n");
}

void print_env_info(t_env *env)
{
    print_map_info(env->map);
    print_camera_info(env->camera);
	ft_printf(BOLD BLUE "[Environment Info]" NC "\n");
	ft_printf("  " GREEN "Mouse:" NC "\n");
	ft_printf("    Click Rotation    : " CYAN "%d" NC "\n", env->mouse_click_rotation);
	ft_printf("    Click Translation : " CYAN "%d" NC "\n", env->mouse_click_translation);
	ft_printf("    Sensibility       : " PURPLE "%f" NC "\n", env->mouse_sensibility);
	ft_printf("    Last Position     : " CYAN "(%d, %d)" NC "\n", env->mouse_last_x, env->mouse_last_y);
	ft_printf("  " GREEN "Scene:" NC "\n");
	ft_printf("    Frames Generated : " PURPLE "%d" NC "\n", env->frames_gen);
	if (env->perspective == 2)
		ft_printf("    Projection       : " PURPLE "Simplest projection" NC "\n");
	else if (env->perspective == 1)
		ft_printf("    Projection       : " PURPLE "Perspective" NC "\n");
	else if (env->perspective == 0)
		ft_printf("    Projection       : " PURPLE "Orthogonale" NC "\n");
	ft_printf("    Z Ordering       : " PURPLE "%d" NC "\n", env->z_ordering);
	ft_printf("    Freecam          : " PURPLE "%d" NC "\n", flip_flop(env->cam_around_focus));
	ft_printf("    Z axe Ratio      : " PURPLE "%f" NC "\n\n", env->z_ratio);
}

void	display_infos(t_env *env)
{
	print_env_info(env);
}

void	print_error(char *str)
{
	ft_printf("%s[Error]%s %s\n", RED, NC, str);
}