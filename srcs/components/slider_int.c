/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:47:09 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/06 17:01:06 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	display_slider_int(t_img *img, const t_int_slider slider)
{
	int	i;
	int	j;

	i = slider.y;
	while (i < slider.y + slider.height)
	{
		j = slider.x;
		while (j < slider.x + slider.width)
		{
			put_pixel_image(img->img_str, j, i, slider.bar_color);
			j++;
		}
		i++;
	}
	draw_filled_circle(slider.x + ((*slider.value - slider.min) * slider.width / (slider.max - slider.min)), slider.y + slider.height / 2, 7, img, slider.point_color);
}

int	slider_mouse_down(const t_int_slider slider, int mouse_x, int mouse_y)
{

	
	return (0);
}

int	slider_mouse_up(const t_int_slider slider, int mouse_x, int mouse_y)
{
	
	return (0);
}

int	slider_mouse_move(const t_int_slider slider, int mouse_x, int mouse_y)
{
	
	return (0);
}

