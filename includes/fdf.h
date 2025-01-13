/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:33:07 by lilefebv          #+#    #+#             */
/*   Updated: 2025/01/13 17:10:03 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "font.h"
# include "structs.h"

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>


#include <stdio.h> // a retirer

# define PI_10D 3.1415926535

# define Z_ORDERING 0
# define WIN_HEIGHT 1080
# define WIN_WIDTH 1920

# define COLOR_MIN 0xFFFFFF
# define COLOR_MAX 0x7B13AB

// refaire toute la docsting en anglais

typedef enum e_mouse_buttons
{
	LEFT_CLICK = 1,
	MIDDLE_CLICK,
	RIGHT_CLICK,
	SCROLL_UP,
	SCROLL_DOWN
}	t_mouse_buttons;

typedef enum e_keys
{
	KEY_SPACE = 32,
	KEY_INF = 44,
	KEY_MINUS = 45,
	KEY_SUP = 46,
	KEY_PLUS = 61,
	KEY_A = 97,
	KEY_C = 99,
	KEY_D = 100,
	KEY_E = 101,
	KEY_F = 102,
	KEY_G = 103,
	KEY_I = 105,
	KEY_L = 108,
	KEY_O = 111,
	KEY_P = 112,
	KEY_Q = 113,
	KEY_S = 115,
	KEY_W = 119,
	KEY_Z = 122,
	KEY_SHIFT = 65505,
	KEY_ESC = 65307
}	t_keys;

typedef enum e_event {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
}   t_event;

void	print_error(char *str);
void	display_infos(t_env *env);
void	exit_free(t_env *env);
int		flip_flop(int nb);
int		get_biggest(int a, int b);

/*╔══════════════════════════════════════════════════════════════════════════╗*/
/*║                                   ENV                                    ║*/
/*╚══════════════════════════════════════════════════════════════════════════╝*/

t_map	*parse_map(char	*map_name);
int		init_all(t_env *env, char **argv);

/*╔══════════════════════════════════════════════════════════════════════════╗*/
/*║                                PROJECTIONS                               ║*/
/*╚══════════════════════════════════════════════════════════════════════════╝*/

void	init_pitch_matrix(double matrix[3][3], double yaw);
void	init_yaw_matrix(double matrix[3][3], double pitch);
void	init_roll_matrix(double matrix[3][3], double roll);
void	init_orthogonal_matrix(double matrix[4][4], t_env *env);
void	init_perspective_matrix(double matrix[4][4], t_env *env);
void	vector_multiply_matrix_3x3(double matrix[3][3], double vector[3]);
void	vector_multiply_matrix_4x4(double matrix[4][4], double vector[4]);
void	multiply_matrix_3x3(double res[3][3], double a[3][3], double b[3][3]);

void	calculate_point_projection(int x, int y, t_env *env);

/*╔══════════════════════════════════════════════════════════════════════════╗*/
/*║                                  CAMERA                                  ║*/
/*╚══════════════════════════════════════════════════════════════════════════╝*/

void	calc_cam_proj(t_env *env, t_camera *camera);
void 	get_local_axes(double axes[3][3], double yaw, double pitch, double roll);
double	calc_scale(t_map *map, t_camera *camera);

void	zoom(t_env *env, int direction);
void	rotate(int x, int y, t_env *env);
void	translate(int x, int y, t_env *env);
void	roll(int direction, t_env *env);
void	wasd_move(int key, t_env *env);

/*╔══════════════════════════════════════════════════════════════════════════╗*/
/*║                                  EVENTS                                  ║*/
/*╚══════════════════════════════════════════════════════════════════════════╝*/

int		mouse_down(int button, int x, int y, void *param);
int		mouse_up(int button, int x, int y, void *param);
int		mouse_move(int x, int y, void *param);
int		keydown(int keycode, void *param);
int		destroy(void *param);

void	events(t_env *env);

/*╔══════════════════════════════════════════════════════════════════════════╗*/
/*║                                 RENDERING                                ║*/
/*╚══════════════════════════════════════════════════════════════════════════╝*/

void	put_pixel_image(char *str, int x, int y, int color);
int		calc_gradiant_point(t_point *point_a, t_point *point_b, double ratio);
int		calc_gradiant_color(int color_a, int color_b, double ratio);
int		is_point_in_frame(t_point point);
void	draw_line(t_point *point_a, t_point *point_b, t_env *env);
void	draw_every_lines(t_env *env);
void	save_lines(t_env *env);
void	quicksort_lines(t_line *lines, int low, int high, int order);

void 	draw_string_to_image(t_img *img, unsigned char font[96][5], t_point p, const char *str);
void 	draw_char_to_image(t_img *img, unsigned char font[96][5], t_point p, char c);

void	render_frame(t_env *env);

#endif