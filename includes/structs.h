/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 14:15:01 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/10 15:50:29 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "libft.h"
# include "components.h"
# include "procedural.h"

typedef unsigned char t_bool;

typedef struct s_vec3
{
    double	x;
	double	y;
	double	z;
}	t_vec3;

/**
 * Coefficients de l'équation du plan ax + by + cz + d = 0
 */
typedef struct s_plane {
    double	a;
	double	b;
	double	c;
	double	d;
}	t_plane;

/**
 * 6 plans du frustum (gauche, droit, bas, haut, proche, lointain)
 */
typedef struct s_frustum {
    t_plane planes[6];
}	t_frustum;

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
 * @param perspective[4][4] 4x4 Matrix that store the perspective calculation
 */
typedef struct s_camera
{
	double	yaw;				/* Yaw angle of the camera */
	double	pitch;				/* Pitch angle of the camera */
	double	roll;				/* Roll angle of the camera */
	double	distance;			/* Distance of the camera to the focus point */
	double	x;					/* X-coordinate of the camera's focus point. */
	double	y;					/* Y-coordinate of the camera's focus point. */
	double	z;					/* Z-coordinate of the camera's focus point. */
	double	proj_x;				/* X-coordinate of the camera's position */
	double	proj_y;				/* Y-coordinate of the camera's position */
	double	proj_z;				/* Z-coordinate of the camera's position */
	double	scale;				/* Global distance variable */
	double	mouse_sensibility;	/* Mouse sensibility */
	int		fov;				/* Field of view of the camera */
	int		zfar;				/* Far clipping plane distance. */
	int		znear;				/* Near clipping plane distance. */
	double	right;				/* Right clipping plane. */
	double	left;				/* Left clipping plane. */
	double	top;				/* Top clipping plane. */
	double	bottom;				/* Bottom clipping plane. */
	double	far;				/* Far clipping plane. */
	double	near;				/* Near clipping plane. */
	double	perspective[4][4];	/* The perspective matrix stored */
	double	local_axes[3][3];	/* Camera local axes */
	t_frustum	frustum;
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
	int		**map;			/* 2D array of integers representing the map */
	int		**color_map;	/* 2D array representing the colors of the map */
	int		*mapl;			/* 1D array of integers representing the map */
	int		*color_mapl;	/* 1D array representing the colors of the map */
	t_bool	*edited;
	int		length;			/* Length of the map */
	int		height;			/* Height of the map */
	int		highest;		/* Highest point on the map */
	int		have_color;		/* Flag indicating if the map has color information */
}	t_map;

typedef struct s_calc_trigo
{
	double	sin_yaw;
	double	cos_yaw;
	double	sin_pitch;
	double	cos_pitch;
	double	sin_roll;
	double	cos_roll;
	
}	t_calc_trigo;

typedef struct s_env t_env;

typedef struct s_brush_c
{
	int				color;
	t_env			*env;
}	t_brush_c;

typedef struct s_thread_param
{
	int				start;
	int				end;
	int				start_ln;
	int				end_ln;
	t_env			*env;
	t_calc_trigo	trigo_calcs;
}	t_thread_param;

typedef struct s_point_select
{
	int				start_mouse_x;
	int				start_mouse_y;
	t_point			*selected_points;
	int				amount_of_points;
	int				is_active;
}	t_point_select;

typedef struct s_painter
{
	int	radius;
	int	color;
	int	is_active;
	int	intensity;
	int	mode;
}	t_painter;

typedef struct s_perlin_noise
{
	unsigned int	seed;
	unsigned int	width;
	unsigned int	height;
	int				min;
	int				max;
	int				x_offset;
	int				y_offset;
	float			scale;
	int				octaves;
	float			persistence;
	float			frequency;
	float			*gradientX;
	float			*gradientY;
	float			*noise;
	int				*heightmap;
	int				vector_grid_size_x;
	int				vector_grid_size_y;
	int				vector_grid_size_total;
	int				vector_grid_division;
	float			min_val;
	float			max_val;
}	t_perlin_noise;

typedef struct s_perlin_map
{
	int				is_perlin_map;
	t_perlin_noise	perlin_noise;
	t_perlin_noise	humidity;
	t_perlin_noise	temperature;
	t_perlin_noise	biome_height;
	t_biome			*biome_map;
}	t_perlin_map;

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
 * @param custom_color Flag indicating if color is determined by height.
 * @param color_preset Color preset number
 * @param sphere_proj Flag indicating if the projection is a spherical proj.
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
	int				mouse_click_select;
	t_point			selected_point;
	int				is_control_down;
	int				is_shift_down;
	int				is_rshift_down;
	t_point_select	points_selection;
	double			mouse_sensibility;
	int				mouse_last_x;
	int				mouse_last_y;
	double			z_ratio;
	int				frames_gen;
	size_t			timestamp_last_frame;
	int				perspective;
	int				z_ordering;
	int				cam_around_focus;
	unsigned char	font[96][5];
	int				display_infos;
	int				custom_color;
	int				color_preset;
	int				sphere_proj;
	int				debug_mode;
	int				points_reduction_factor;
	int				auto_point_reduc;
	int				line_algo;
	int				proc_amount;
	pthread_t		*threads;
	t_thread_param	*threads_params;
	int				protect_data_races;
	t_painter		painter;
	t_button		color_buttons[52];
	t_int_slider	brush_size_slider;
	t_int_slider	brush_intensity_slider;
	t_text_input	save_input;
	t_perlin_map	procedural;
}	t_env;

#endif
