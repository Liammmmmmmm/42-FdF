/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   components.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:39:10 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/06 16:42:14 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPONENTS_H
# define COMPONENTS_H

# include "libft.h"

/**
 * @struct s_img
 * @brief Structure representing an image with its properties.
 * 
 * @param img Pointer to identify the image.
 * @param img_str String containing all the pixels of the image.
 * @param img_depth Contain the depth of each pixel (from camera)
 * @param bits Number of bits per pixel.
 * @param size_line Size of the img_str.
 * @param endian Indicates the endianness of the image.
 */
typedef struct s_img
{
	void	*img;		/* Pointer to identify the image */
	char	*img_str;	/* String containing all the pixels of the image */
	float	*img_depth;	/* Contain the depth of each pixel (from camera) */
	pthread_mutex_t	img_mutex;
	int		is_mutex_ok;
	int		bits;		/* Number of bits per pixel */
	int		size_line;	/* Size of the img_str */
	int		endian;		/* Indicates the endianness of the image */
}	t_img;

typedef struct s_button
{
	int		x;
	int		y;
	int		width;
	int		height;
	int		border_color;
	int		background_color;
	void	*param;
	void	(*action)(void *);
}	t_button;

void	display_button(t_img *img, const t_button button);
int		button_action(const t_button button, int mouse_x, int mouse_y);

typedef struct s_int_slider
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	point_color;
	int	bar_color;
	int	min;
	int	max;
	int *value;
}	t_int_slider;

void	display_slider_int(t_img *img, const t_int_slider slider);
int		slider_mouse_down(const t_button button, int mouse_x, int mouse_y);
int		slider_mouse_up(const t_button button, int mouse_x, int mouse_y);
int		slider_mouse_move(const t_button button, int mouse_x, int mouse_y);

#endif
