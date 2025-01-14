/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 14:03:37 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/14 14:11:19 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	char_to_img(t_img *img, unsigned char font[96][5], t_point p, char c)
{
	int	i;
	int	j;

	if (c < 32 || c > 127)
		return ;
	i = -1;
	c -= 32;
	while (++i < 5)
	{
		j = -1;
		while (++j < 7)
			if (font[(int)c][i] & (1 << j))
				put_pixel_image(img->img_str, p.x + i, p.y + j, p.color);
	}
}

void	string_to_img(t_img *img, unsigned char font[96][5],
	t_point p, const char *str)
{
	int	xstart;

	xstart = p.x;
	while (*str)
	{
		char_to_img(img, font, p, *str);
		p.x += 6;
		if (*str == '\n')
		{
			p.x = xstart;
			p.y += 14;
		}
		str++;
	}
}
