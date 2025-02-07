/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   components.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:39:10 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/07 16:26:38 by lilefebv         ###   ########lyon.fr   */
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
	int		border_color_on_click;
	int		background_color_on_click;
	int		is_clicked;
	char	*text;
	void	*param;
	void	(*action)(void *);
}	t_button;

void	display_button(t_img *img, const t_button button, unsigned char font[96][5]);
int		button_action(t_button *button, int mouse_x, int mouse_y);
int		button_release(t_button *button);

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
	int	is_clicked;
}	t_int_slider;

void	display_slider_int(t_img *img, const t_int_slider slider);
int		slider_mouse_down(t_int_slider *slider, int mouse_x, int mouse_y);
int		slider_mouse_up(t_int_slider *slider);
int		slider_mouse_move(t_int_slider *slider, int mouse_x);

typedef struct s_text_input
{
	int		x;
	int		y;
	int		width;
	int		height;
	int		border_color;
	int		background_color;
	int		border_color_focus;
	int		is_focused;
	int		padding_left;
	int		max_char;
	int		text_color;
	char	text[256];
	char	placeholder[256];
	int		cursor_pos;
}	t_text_input;

void	display_text_input(t_img *img, t_text_input *text_input, unsigned char font[96][5]);
int		text_input_focus(t_text_input *text_input, int mouse_x, int mouse_y);
int		text_input_type(t_text_input *text_input, int key, int is_shift_down);

#endif
