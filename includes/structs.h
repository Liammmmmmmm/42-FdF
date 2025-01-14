/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 14:15:01 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/14 17:47:27 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/**
 * @struct s_img
 * @brief Structure representing an image with its properties.
 * 
 * @param img Pointer to identify the image.
 * @param img_str String containing all the pixels of the image.
 * @param bits Number of bits per pixel.
 * @param size_line Size of the img_str.
 * @param endian Indicates the endianness of the image.
 */
typedef struct s_img
{
	void	*img;		/* Pointer to identify the image */
	char	*img_str;	/* String containing all the pixels of the image */
	int		bits;		/* Number of bits per pixel */
	int		size_line;	/* Size of the img_str */
	int		endian;		/* Indicates the endianness of the image */
}	t_img;

/**
 * @struct s_color
 * @brief Structure representing a color with RGB components.
 * 
 * @param r Red component of the color.
 * @param g Green component of the color.
 * @param b Blue component of the color.
 */
typedef struct s_color
{
	unsigned char	r;	/* Red component of the color. */
	unsigned char	g;	/* Green component of the color. */
	unsigned char	b;	/* Blue component of the color. */
}	t_color;

/**
 * @struct s_point
 * @brief Structure representing a point in 2D space with a color.
 * 
 * @param x X-coordinate of the point on the screen.
 * @param y Y-coordinate of the point on the screen.
 * @param z Depth of the point.
 * @param color Color of the point.
 */
typedef struct s_point
{
	int		x;		/* X-coordinate of the point on the screen. */
	int		y;		/* Y-coordinate of the point on the screen. */
	double	z;		/* Depth of the point. */
	int		color;	/* Color of the point. */
}	t_point;

/**
 * @struct s_line
 * @brief Structure representing a line between two points.
 * 
 * @param start Pointer to the starting point of the line.
 * @param end Pointer to the ending point of the line.
 * @param depth Depth of the line.
 */
typedef struct s_line
{
	t_point	*start;	/* Pointer to the starting point of the line. */
	t_point	*end;	/* Pointer to the ending point of the line. */
	float	depth;	/* Depth of the line. */
}	t_line;

/**
 * @struct s_camera
 * @brief Structure representing a camera with its rotation and position
 *        parameters.
 * 
 * @param yaw Yaw angle (rotation around the z-axis).
 * @param pitch Pitch angle (rotation around the x-axis).
 * @param roll Roll angle (rotation around the y-axis).
 * @param distance Distance from the camera to the focus point.
 * @param x X-coordinate of the camera's focus point.
 * @param y Y-coordinate of the camera's focus point.
 * @param z Z-coordinate of the camera's focus point.
 * @param proj_x X-coordinate of the camera considering the distance.
 * @param proj_y Y-coordinate of the camera considering the distance.
 * @param proj_z Z-coordinate of the camera considering the distance.
 * @param scale Global distance variable.
 * @param mouse_sensibility Sensitivity of the mouse for camera movement.
 * @param fov Field of view of the camera.
 * @param zfar Far clipping plane distance.
 * @param znear Near clipping plane distance.
 * @param right Right clipping plane.
 * @param left Left clipping plane.
 * @param top Top clipping plane.
 * @param bottom Bottom clipping plane.
 * @param far Far clipping plane.
 * @param near Near clipping plane.
 */
typedef struct s_camera
{
	double	yaw;
	double	pitch;
	double	roll;
	double	distance;
	double	x;
	double	y;
	double	z;
	double	proj_x;
	double	proj_y;
	double	proj_z;
	double	scale;
	double	mouse_sensibility;
	int		fov;
	int		zfar;
	int		znear;
	double	right;
	double	left;
	double	top;
	double	bottom;
	double	far;
	double	near;
}	t_camera;

/**
 * @struct s_map
 * @brief Structure representing a map with its data and dimensions.
 * 
 * @param map 2D array of integers representing the map, with each int
 *            corresponding to the height of a point.
 * @param color_map 2D array of integers representing the colors of the map.
 * @param length Length of the map.
 * @param height Height of the map.
 * @param highest Highest point on the map.
 * @param have_color Flag indicating if the map has color information.
 */
typedef struct s_map
{
	int	**map;
	int	**color_map;
	int	length;
	int	height;
	int	highest;
	int	have_color;
}	t_map;

/**
 * @struct s_env
 * @brief Structure representing the environment containing all the information
 *        about the current scene.
 * 
 * @param map Pointer to the map structure.
 * @param camera Pointer to the camera structure.
 * @param point_list Pointer to the list of points.
 * @param lines Pointer to the list of lines.
 * @param line_amount Number of lines.
 * @param img Pointer to the image structure.
 * @param mlx Pointer to the MLX instance.
 * @param mlx_win Pointer to the MLX window.
 * @param mouse_click_rotation Flag indicating if the mouse is clicked for
 *                             rotation.
 * @param mouse_click_translation Flag indicating if the mouse is clicked for
 *                                translation.
 * @param mouse_sensibility Sensitivity of the mouse for camera movement.
 * @param mouse_last_x Last x-coordinate of the mouse.
 * @param mouse_last_y Last y-coordinate of the mouse.
 * @param z_ratio Ratio for the z-axis scaling.
 * @param frames_gen Number of frames generated.
 * @param perspective Flag indicating if perspective projection is enabled.
 * @param z_ordering Flag indicating if z-ordering is enabled.
 * @param cam_around_focus Flag indicating if the camera is rotating around the
 *                         focus point.
 * @param font Font data for rendering text.
 * @param display_infos Flag indicating if information display is enabled.
 * @param color_by_height Flag indicating if color is determined by height.
 */
typedef struct s_env
{
	t_map			*map;
	t_camera		*camera;
	t_point			*point_list;
	t_line			*lines;
	int				line_amount;
	t_img			*img;
	void			*mlx;
	void			*mlx_win;
	int				mouse_click_rotation;
	int				mouse_click_translation;
	double			mouse_sensibility;
	int				mouse_last_x;
	int				mouse_last_y;
	double			z_ratio;
	int				frames_gen;
	int				perspective;
	int				z_ordering;
	int				cam_around_focus;
	unsigned char	font[96][5];
	int				display_infos;
	int				color_by_height;
}	t_env;

#endif
