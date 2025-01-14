/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 14:15:01 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/14 15:51:15 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_img
{
	void	*img;		/* pointer qui permet d'identifier l'image */
	char	*img_str;	/* string contenant tous les pixels de l'image */
	int		bits;		/* nombre de bits par pixels */
	int		size_line;	/*  taille de la img_str*/
	int		endian;		/* permet de signifier la fin d'une image*/
}	t_img;

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;

/**
 * @struct s_point
 * @brief Structure représentant un point dans l'espace 2D avec une couleur.
 * 
 * @param x Coordonnée x du point sur l'ecran.
 * @param y Coordonnée y du point sur l'ecran.
 * @param color Couleur du point.
 */
typedef struct s_point
{
	int		x;
	int		y;
	double	z;
	int		color;
}	t_point;

typedef struct s_line
{
	t_point	*start;
	t_point	*end;
	float	depth;
}	t_line;

/**
 * @struct s_camera
 * @brief Structure représentant une caméra avec ses paramètres de rotation 
 *        et de position.
 * 
 * @param yaw Angle de lacet (rotation autour de l'axe y).
 * @param pitch Angle de tangage (rotation autour de l'axe x).
 * @param roll Angle de roulis (rotation autour de l'axe z).
 * @param distance Distance de la caméra au point de focus.
 * @param x Position x du point de focus de la caméra.
 * @param y Position y du point de focus de la caméra.
 * @param z Position z du point de focus de la caméra.
 * @param proj_x Position x de la caméra en prenant en compte la distance.
 * @param proj_y Position y de la caméra en prenant en compte la distance.
 * @param proj_z Position z de la caméra en prenant en compte la distance.
 * @param scale Variable qui pourrait etre considerre de 'distance global'.
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
 * @brief Structure représentant une carte avec ses données et ses dimensions.
 * 
 * @param map Tableau d'int représentant la carte, avec chaque int
 *            correspondant a la hauteur d'un point
 * @param color_map Tableau d'int représentant les couleurs de la carte.
 * @param length Longueur de la carte.
 * @param height Hauteur de la carte.
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
 * @brief Structure environement contenant toutes les infos sur la scene en
 *        cours.
 * 
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
	int				win_width;
	int				win_height;
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
