/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:47:09 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/07 12:21:46 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	display_button(t_img *img, const t_button button, unsigned char font[96][5])
{
	int	i;
	int	j;
	t_point start;

	i = button.x;
	while (i <= button.x + button.width)
	{
		put_pixel_image(img->img_str, i, button.y, button.border_color);
		put_pixel_image(img->img_str, i, button.y + button.height, button.border_color);
		i++;
	}
	i = button.y + 1;
	while (i < button.y + button.height)
	{
		put_pixel_image(img->img_str, button.x, i, button.border_color);
		put_pixel_image(img->img_str, button.x + button.width, i, button.border_color);
		j = button.x + 1;
		while (j < button.x + button.width)
		{
			put_pixel_image(img->img_str, j, i, button.background_color);
			j++;
		}
		i++;
	}
	if (button.text)
	{
		start.x = button.x + button.width / 2 - (string_size(button.text) / 2);
		start.y = button.y + button.height / 2 - 3;
		start.color = 0;
		string_to_img(img, font, start, button.text);
	}
}

int	button_action(const t_button button, int mouse_x, int mouse_y)
{
	if (button.x <= mouse_x && button.x + button.width >= mouse_x
		&& button.y <= mouse_y && button.y + button.height >= mouse_y)
	{
		button.action(button.param);
		return (1);
	}
	return (0);
}
