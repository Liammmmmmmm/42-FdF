/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:39:31 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/07 16:19:29 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_putnbr_hex_fd(int n, int fd)
{
	if (n <= 15)
		write(fd, &"0123456789abcdef"[n], 1);
	else
	{
		ft_putnbr_hex_fd(n / 16, fd);
		write(fd, &"0123456789abcdef"[n % 16], 1);
	}
}

void save_map(const char *filename, t_env *env)
{
	int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1) {
		print_error("Error opening file");
		return ;
	}
	int	x;
	int	y;

	y = 0;
	while (y < env->map->height)
	{
		x = 0;
		while (x < env->map->length)
		{
			if (x != 0)
				write(fd, " ", 1);
			ft_putnbr_fd(env->map->map[y][x], fd);
			if (env->map->color_map[y][x] != 0xffffff)
			{
				write(fd, ",0x", 3);
				ft_putnbr_hex_fd(env->map->color_map[y][x], fd);
			}
			x++;
		}
		write(fd, "\n", 1);
		y++;
	}
	close(fd);
}

void	save_map_button(void *param)
{
	if (((t_brush_c *)param)->env->save_input.text[0] == 0)
	{
		ft_strlcpy(((t_brush_c *)param)->env->save_input.text, "no-name", 20);
		((t_brush_c *)param)->env->save_input.cursor_pos = 7;
	}
	ft_strlcat(((t_brush_c *)param)->env->save_input.text, ".fdf", 256);
	save_map(((t_brush_c *)param)->env->save_input.text, ((t_brush_c *)param)->env);
	((t_brush_c *)param)->env->save_input.text[((t_brush_c *)param)->env->save_input.cursor_pos] = 0;
}
