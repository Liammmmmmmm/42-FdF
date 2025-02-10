/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:57:10 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/10 11:17:25 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_camera_info(t_camera *c)
{
	ft_printf(BOLD BLUE "[Camera Info]" NC "\n");
	ft_printf("  " GREEN "Rotation:" NC "\n");
	ft_printf("    Yaw   : " YELLOW "%f°" NC "\n", (c->pitch * 180 / PI_10D));
	ft_printf("    Pitch : " YELLOW "%f°" NC "\n", (c->yaw * 180 / PI_10D));
	ft_printf("    Roll  : " YELLOW "%f°" NC "\n", (c->roll * 180 / PI_10D));
	ft_printf("  " GREEN "Position:" NC "\n");
	ft_printf("    Focus Point : "CYAN"(%f, %f, %f)"NC"\n", c->x, c->y, c->z);
	ft_printf("    Real pos    : "CYAN"(%f, %f, %f)"NC"\n",
		c->proj_x, c->proj_y, c->proj_z);
	ft_printf("  " GREEN "Parameters:" NC "\n");
	ft_printf("    Distance      : " PURPLE "%f" NC "\n", c->distance);
	ft_printf("    Scale         : " PURPLE "%f" NC "\n", c->scale);
	ft_printf("    Mouse Sens.   : "PURPLE"%f"NC"\n", c->mouse_sensibility);
	ft_printf("    FOV           : " PURPLE "%d" NC "\n", c->fov);
	ft_printf("    Near Clip     : " PURPLE "%d" NC "\n", c->znear);
	ft_printf("    Far Clip      : " PURPLE "%d" NC "\n", c->zfar);
	ft_printf("    Right/Left    : "CYAN"%f" NC " / "CYAN"%f"NC"\n",
		c->right, c->left);
	ft_printf("    Top/Bottom    : "CYAN"%f" NC " / "CYAN"%f"NC"\n",
		c->top, c->bottom);
	ft_printf("    Near/Far Plane: "CYAN"%f" NC " / "CYAN"%f"NC"\n",
		c->near, c->far);
	ft_printf("\n");
}

void	print_map_info(t_map *map)
{
	ft_printf(BOLD BLUE "[Map Info]" NC "\n");
	ft_printf("  " GREEN "Dimensions:" NC "\n");
	ft_printf("    Length : " YELLOW "%d" NC "\n", map->length);
	ft_printf("    Height : " YELLOW "%d" NC "\n\n", map->height);
}

void	display_infos(t_env *env)
{
	print_map_info(env->map);
	print_camera_info(env->camera);
	ft_printf(BOLD BLUE "[Environment Info]" NC "\n");
	ft_printf("  " GREEN "Mouse:" NC "\n");
	ft_printf("    Click Rotation    : " CYAN "%d" NC "\n",
		env->mouse_click_rotation);
	ft_printf("    Click Translation : " CYAN "%d" NC "\n",
		env->mouse_click_translation);
	ft_printf("    Sensibility       : " PURPLE "%f" NC "\n",
		env->mouse_sensibility);
	ft_printf("    Last Position     : " CYAN "(%d, %d)" NC "\n",
		env->mouse_last_x, env->mouse_last_y);
	ft_printf("  " GREEN "Scene:" NC "\n");
	ft_printf("    Frames Generated : " PURPLE "%d" NC "\n", env->frames_gen);
	if (env->perspective == 2)
		ft_printf("    Projection       : "PURPLE"Simplest projection"NC"\n");
	else if (env->perspective == 1)
		ft_printf("    Projection       : " PURPLE "Perspective" NC "\n");
	else if (env->perspective == 0)
		ft_printf("    Projection       : " PURPLE "Orthogonale" NC "\n");
	ft_printf("    Z Ordering       : " PURPLE "%d" NC "\n", env->z_ordering);
	ft_printf("    Freecam          : " PURPLE "%d" NC "\n",
		flip_flop(env->cam_around_focus));
	ft_printf("    Z axe Ratio      : " PURPLE "%f" NC "\n\n", env->z_ratio);
}

void	print_error(char *str)
{
	ft_printf(RED "[Error]" NC " %s\n", str);
}

void	print_info(char *str)
{
	ft_printf(BLUE "[INFO]" NC " %s\n", str);
}
