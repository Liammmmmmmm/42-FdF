/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:33:07 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/07 17:11:49 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>

# define PI_10D 3.1415926535

// refaire toute la docsting en anglais

typedef enum e_mouse_buttons
{
	LEFT_CLICK = 1,
	MIDDLE_CLICK,
	RIGHT_CLICK,
	SCROLL_UP,
	SCROLL_DOWN
}	t_mouse_buttons;

typedef enum e_event {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
}   t_event;

typedef struct	s_img
{
	void  *img;      /* pointer qui permet d'identifier l'image */
	char  *img_str;  /* string contenant tous les pixels de l'image */
	int   bits;      /* nombre de bits par pixels */
	int   size_line; /*  taille de la img_str*/
	int   endian;    /* permet de signifier la fin d'une image*/
}               t_img;

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
	int	x;
	int	y;
	int	color;
}	t_point;

/**
 * @struct s_camera
 * @brief Structure représentant une caméra avec ses paramètres de rotation et de position.
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
}	t_map;

/**
 * @struct s_env
 * @brief Structure environement contenant toutes les infos sur la scene en cours.
 * 
 */
typedef struct s_env
{
	t_map		*map;
	t_camera	*camera;
	t_point		**point_list;
	t_img		*img;
	void		*mlx;
	void		*mlx_win;
	int			mouse_click_rotation;
	int			mouse_click_translation;
	double		mouse_sensibility;
	int			mouse_last_x;
	int			mouse_last_y;
}	t_env;

void	print_error(char *str);
t_map	*parse_map(char	*map_name);

/*╔══════════════════════════════════════════════════════════════════════════╗*/
/*║                              PROJECTIONS                                 ║*/
/*╚══════════════════════════════════════════════════════════════════════════╝*/

void	init_yaw_matrix(double matrix[3][3], double yaw);
void	init_pitch_matrix(double matrix[3][3], double pitch);
void	init_roll_matrix(double matrix[3][3], double roll);
void	vector_multiply_matrix(double matrix[3][3], double vector[3]);

void	calculate_point_projection(int x, int y, t_env *env);

/*╔══════════════════════════════════════════════════════════════════════════╗*/
/*║                               RENDERING                                  ║*/
/*╚══════════════════════════════════════════════════════════════════════════╝*/

void	put_pixel_image(char *str, int x, int y, int color);


#endif