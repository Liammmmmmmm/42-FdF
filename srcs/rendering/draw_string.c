/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 14:03:37 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/07 12:17:00 by lilefebv         ###   ########lyon.fr   */
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

void	string_to_img(t_img *img, unsigned char font[96][5], t_point p, char *str)
{
	int	xstart;
	int	i;

	xstart = p.x;
	while (*str)
	{
		if (*str == '\033' && *(str + 1))
		{
			if (*(str + 1) == '#' && *(str + 2))
			{
				i = 0;
				while (ft_strchr("0123456789ABCDEF", str[2 + i]) && i < 6)
					i++;
				p.color = ft_atoi_base_limited(str + 2, "0123456789ABCDEF", 6);
				str = str + i + 1;
			}
		}
		else if (*str == '\n')
		{
			p.x = xstart;
			p.y += 14;
		}
		else
		{
			char_to_img(img, font, p, *str);
			p.x += 6;
		}
		str++;
	}
}

int	string_size(char *str)
{
	int	xstart;
	int	i;
	int	size;

	xstart = 0;
	size = 0;
	while (*str)
	{
		if (*str == '\033' && *(str + 1))
		{
			if (*(str + 1) == '#' && *(str + 2))
			{
				i = 0;
				while (ft_strchr("0123456789ABCDEF", str[2 + i]) && i < 6)
					i++;
				str = str + i + 1;
			}
		}
		else if (*str == '\n')
			return (size);
		else
			size += 6;
		str++;
	}
	if (size > 0)
		size--;
	return (size);
}
