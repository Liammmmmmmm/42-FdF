/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:33:07 by lilefebv          #+#    #+#             */
/*   Updated: 2025/02/10 11:17:58 by lilefebv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "components.h"
# include "structs.h"

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>
# include <float.h>
# include <sys/sysinfo.h>
# include <pthread.h>

# define PI_10D 3.1415926535

# define Z_ORDERING 0
# define WIN_HEIGHT 1080
# define WIN_WIDTH 1920

# define COLOR_MIN 0xFFFFFF
# define COLOR_MAX 0x7B13AB

// How many pixel from the mouse a point can be selected
# define SELECT_RANGE 5

# define ERROR_MLX "MLX initialization failed"

# define CONTROLS "INFOS : Controls\n  \033#AFE1AFCamera\033#FFFFFF :\n    \033#87CEEB[ESC]\033#FFFFFF Close window\n   \
	\033#87CEEB[LMB]\033#FFFFFF Rotate\n    \033#87CEEB[MMB]\033#FFFFFF Translate\n    \033#87CEEB[SCROLL]\033#FFFFFF Zoom/dezoom\n   \
	\033#87CEEB[F]\033#FFFFFF Toggle freecam\n    \033#87CEEB[W]\033#FFFFFF Move forward\n    \033#87CEEB[A]\033#FFFFFF Move left\n   \
	\033#87CEEB[S]\033#FFFFFF Move backward\n    \033#87CEEB[D]\033#FFFFFF Move right\n    \033#87CEEB[SPACE]\033#FFFFFF Move up\n   \
	\033#87CEEB[SHIFT]\033#FFFFFF Move down\n    \033#87CEEB[Q]\033#FFFFFF Roll left\n    \033#87CEEB[E]\033#FFFFFF Roll right\n   \
	\033#87CEEB[<]\033#FFFFFF Reduce FOV\n    \033#87CEEB[>]\033#FFFFFF Increase FOV\n  \033#AFE1AFRender\033#FFFFFF :\n    \033#87CEEB[-]\033#FFFFFF Shrink z axe\
	\n    \033#87CEEB[+]\033#FFFFFF Extend z axe\n    \033#87CEEB[G]\033#FFFFFF Toggle custom color\n   \
	\033#87CEEB[NUMPAD]\033#FFFFFF Set color preset\n    \033#87CEEB[L]\033#FFFFFF \"Normal\" view\n    \033#87CEEB[P]\033#FFFFFF Perspective\n\
	   \033#87CEEB[O]\033#FFFFFF Toggle sphere projection\n    \033#87CEEB[Z]\033#FFFFFF Toggle z ordering\n\
	   \033#87CEEB[H]\033#FFFFFF Toggle auto point reduction\n    \033#87CEEB[J]\033#FFFFFF Increase amount of displayed points\n\
	   \033#87CEEB[K]\033#FFFFFF Decrease amount of displayed points\n\
	   \033#87CEEB[RMB]\033#FFFFFF Select point\n    \033#87CEEB[B]\033#FFFFFF Decrease point altitude\n    \033#87CEEB[N]\033#FFFFFF Increase point altitude\n  \033#AFE1AFOther\033#FFFFFF :\n   \
	\033#87CEEB[C]\033#FFFFFF Toggle controls menu\n    \033#87CEEB[I]\033#FFFFFF Toggle informations menu"

# define LIVE_INFO "INFOS : Environment\n  \033#AFE1AFMap\033#FFFFFF :\n    Length : \033#DA70D6%d\033#FFFFFF\n   \
	Width  : \033#DA70D6%d\033#FFFFFF\n  \033#AFE1AFCamera\033#FFFFFF :\n    \033#87CEEBRotations\033#FFFFFF:\n      Yaw   : \033#DA70D6%f\033#FFFFFF\n     \
	Pitch : \033#DA70D6%f\033#FFFFFF\n      Roll  : \033#DA70D6%f\033#FFFFFF\n    \033#87CEEBPosition\033#FFFFFF :\n     \
	Focus point : (\033#DA70D6%f\033#FFFFFF, \033#DA70D6%f\033#FFFFFF, \033#DA70D6%f\033#FFFFFF)\n      Real point  : (\033#DA70D6%f\033#FFFFFF, \033#DA70D6%f\033#FFFFFF, \033#DA70D6%f\033#FFFFFF)\n   \
	\033#87CEEBLocal axes\033#FFFFFF :\n      F : (\033#DA70D6%f\033#FFFFFF, \033#DA70D6%f\033#FFFFFF, \033#DA70D6%f\033#FFFFFF)\n      U : (\033#DA70D6%f\033#FFFFFF, \033#DA70D6%f\033#FFFFFF, \033#DA70D6%f\033#FFFFFF)\n      R : (\033#DA70D6%f\033#FFFFFF, \033#DA70D6%f\033#FFFFFF, \033#DA70D6%f\033#FFFFFF)\n   \
	\033#87CEEBParameters\033#FFFFFF :\n      Distance      : \033#DA70D6%f\033#FFFFFF\n      Scale         : \033#DA70D6%f\033#FFFFFF\n     \
	Mouse Sens.   : \033#DA70D6%f\033#FFFFFF\n      FOV           : \033#DA70D6%d\033#FFFFFF\n     \
	Near Clip     : \033#DA70D6%d\033#FFFFFF\n      Far Clip      : \033#DA70D6%d\033#FFFFFF\n     \
	Right/Left    : \033#DA70D6%f\033#FFFFFF / \033#DA70D6%f\033#FFFFFF\n      Top/Bottom    : \033#DA70D6%f\033#FFFFFF / \033#DA70D6%f\033#FFFFFF\n     \
	Near/Far Plane: \033#DA70D6%f\033#FFFFFF / \033#DA70D6%f\033#FFFFFF\n  \033#AFE1AFGlobal\033#FFFFFF\n    \033#87CEEBMouse\033#FFFFFF :\n     \
	Click Rotation    : \033#DA70D6%d\033#FFFFFF\n      Click Translation : \033#DA70D6%d\033#FFFFFF\n     \
	Sensibility       : \033#DA70D6%f\033#FFFFFF\n      Last Position     : (\033#DA70D6%d\033#FFFFFF, \033#DA70D6%d\033#FFFFFF)\n   \
	\033#87CEEBScene\033#FFFFFF :\n      Frames Generated : \033#DA70D6%d\033#FFFFFF\n      FPS              : \033#DA70D6%f\033#FFFFFF\n      Sphere           : \033#DA70D6%d\033#FFFFFF\n     \
	Projection       : \033#DA70D6%s\033#FFFFFF\n      Z Ordering       : \033#DA70D6%d\033#FFFFFF\n     \
	Freecam          : \033#DA70D6%d\033#FFFFFF\n      Z axe Ratio      : \033#DA70D6%f\033#FFFFFF\n     \
	Custom color     : \033#DA70D6%d\033#FFFFFF\n      Color preset     : \033#DA70D6%d\033#FFFFFF\n     \
	Auto point reduc : \033#DA70D6%d\033#FFFFFF\n      Diplayed points  : 1/\033#DA70D6%d\033#FFFFFF"

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
	KEY_B = 98,
	KEY_C = 99,
	KEY_D = 100,
	KEY_E = 101,
	KEY_F = 102,
	KEY_G = 103,
	KEY_H = 104,
	KEY_I = 105,
	KEY_J = 106,
	KEY_K = 107,
	KEY_L = 108,
	KEY_N = 110,
	KEY_O = 111,
	KEY_P = 112,
	KEY_Q = 113,
	KEY_R = 114,
	KEY_S = 115,
	KEY_T = 116,
	KEY_V = 118,
	KEY_W = 119,
	KEY_X = 120,
	KEY_Z = 122,
	NUM_0 = 65438,
	NUM_1 = 65436,
	NUM_2 = 65433,
	NUM_3 = 65435,
	NUM_4 = 65430,
	NUM_5 = 65437,
	NUM_6 = 65432,
	NUM_7 = 65429,
	NUM_8 = 65431,
	NUM_9 = 65434,
	KEY_ESC = 65307,
	KEY_SHIFT = 65505,
	KEY_RSHIFT = 65506,
	KEY_CTRL_LEFT = 65507,
}	t_keys;

typedef enum e_event
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
}	t_event;

/*╔══════════════════════════════════════════════════════════════════════════╗*/
/*║                                   ENV                                    ║*/
/*╚══════════════════════════════════════════════════════════════════════════╝*/

size_t	get_time(void);

/**
 * @brief Parse the map file.
 *
 * This function parses the map file and initializes the map structure.
 *
 * @param map_name The name of the map file.
 * 
 * @return A pointer to the initialized map structure, or NULL on failure.
 */
t_map	*parse_map(char	*map_name);

/**
 * @brief Initialize all environment variables.
 *
 * This function initializes all environment variables, including the map,
 * camera, points, lines, and image.
 *
 * @param env The environment structure.
 * @param argv The command-line arguments.
 * @return 1 on success, 0 on failure.
 */
int		init_all(t_env *env, int argc, char **argv);

/**
 * @brief Print an error message.
 *
 * This function prints an error message to the console.
 *
 * @param str The error message to print.
 */
void	print_error(char *str);

/**
 * @brief Print an info message.
 *
 * This function prints an info message to the console.
 *
 * @param str The info message to print.
 */
void	print_info(char *str);

/**
 * @brief Display information about the environment.
 *
 * This function displays information about the environment, including the map,
 * camera, and other settings.
 *
 * @param env The environment structure.
 */
void	display_infos(t_env *env);

/**
 * @brief Free all allocated memory by the map.
 *
 * Why not free_map() instead of fr_map() ? This question is relevant and THIS
 * is the result of our magnificient norm, and to gain 2 char on a line, this
 * function name have been cropped.
 *
 * @param env The environment structure.
 */
void	fr_map(t_env *env, int free_env);
void	fr_cam(t_env *env, int free_env);
void	fr_pts(t_env *env, int free_env);
void	free_lns(t_env *env, int free_env);

/**
 * @brief Free all allocated memory.
 *
 * This function frees all allocated memory by the program.
 *
 * @param env The environment structure.
 */
void	exit_free(t_env *env);

/**
 * @brief Toggle a boolean value.
 *
 * This function toggles a boolean value between 0 and 1.
 *
 * @param nb The boolean value to toggle.
 * 
 * @return The toggled boolean value.
 */
int		flip_flop(int nb);

int	sitch_mode(int nb, int max);

/**
 * @brief Get the larger of two integers.
 *
 * This function returns the larger of two integers.
 *
 * @param a The first integer.
 * @param b The second integer.
 * 
 * @return The larger of the two integers.
 */
int		get_biggest(int a, int b);

/**
 * @brief Count the number of lines in a map file.
 *
 * This function counts the number of lines in a map file and checks if the
 * lines are valid.
 *
 * @param map_name The name of the map file.
 * @param map The map structure to update.
 * 
 * @return 1 on success, 0 on failure.
 */
int		count_file_lines(char *map_name, t_map *map);

/**
 * @brief Fill a line in the map structure.
 *
 * This function fills a line in the map structure with the parsed data.
 *
 * @param line The line to fill.
 * @param map The map structure to update.
 * @param i The index of the line.
 * 
 * @return 1 on success, 0 on failure.
 */
int		fill_line(char *line, t_map *map, int i);

/**
 * @brief Allocate memory for a line in the map structure.
 *
 * This function allocates memory for a line in the map structure.
 *
 * @param map The map structure to update.
 * @param i The index of the line.
 * 
 * @return 1 on success, 0 on failure.
 */
int		malloc_line_map(t_map *map, int i);

/*╔══════════════════════════════════════════════════════════════════════════╗*/
/*║                                PROJECTIONS                               ║*/
/*╚══════════════════════════════════════════════════════════════════════════╝*/

/**
 * @brief Initializes the yaw matrix.
 * 
 * Sets up the yaw rotation matrix for rotation around the z-axis.
 *
 * @param matrix[3][3] The 3x3 matrix to initialize.
 * @param yaw The yaw angle in radians.
 */
void	init_yaw_matrix(double matrix[3][3], t_calc_trigo trigo_calcs);

/**
 * @brief Initializes the roll matrix.
 * 
 * Sets up the roll rotation matrix for rotation around the y-axis.
 *
 * @param matrix[3][3] The 3x3 matrix to initialize.
 * @param roll The roll angle in radians.
 */
void	init_roll_matrix(double matrix[3][3], t_calc_trigo trigo_calcs);

/**
 * @brief Initializes the pitch matrix.
 * 
 * Sets up the pitch rotation matrix for rotation around the x-axis.
 *
 * @param matrix[3][3] The 3x3 matrix to initialize.
 * @param pitch The pitch angle in radians.
 */
void	init_pitch_matrix(double matrix[3][3], t_calc_trigo trigo_calcs);

/**
 * @brief Initializes the perspective projection matrix.
 * 
 * Sets up the perspective projection matrix based on the camera's
 * field of view and near/far planes.
 *
 * @param matrix[4][4] The 4x4 matrix to initialize.
 * @param env The environment containing the camera parameters.
 */
void	init_perspective_matrix(double matrix[4][4], t_env *env);

/**
 * @brief Initializes the orthogonal projection matrix.
 * 
 * Sets up the orthogonal projection matrix based on the camera's view volume.
 *
 * @param matrix[4][4] The 4x4 matrix to initialize.
 * @param env The environment containing the camera parameters.
 */
void	init_orthogonal_matrix(double matrix[4][4], t_env *env);

/**
 * @brief Multiplies a 3D vector by a 3x3 matrix.
 * 
 * Multiplies the given 3D vector by the specified 3x3 matrix and updates
 * the vector with the result.
 *
 * @param matrix The 3x3 matrix to multiply with.
 * @param vector The 3D vector to be multiplied.
 */
void	vector_multiply_matrix_3x3(double matrix[3][3], double vector[3]);

/**
 * @brief Multiplies a 4D vector by a 4x4 matrix.
 * 
 * Multiplies the given 4D vector by the specified 4x4 matrix and updates
 * the vector with the result.
 *
 * @param matrix The 4x4 matrix to multiply with.
 * @param vector The 4D vector to be multiplied.
 */
void	vector_multiply_matrix_4x4(double matrix[4][4], double vector[4]);

/**
 * @brief Multiplies two 3x3 matrices.
 * 
 * Multiplies matrix a by matrix b and stores the result in matrix res.
 *
 * @param res The resulting 3x3 matrix.
 * @param a The first 3x3 matrix.
 * @param b The second 3x3 matrix.
 */
void	multiply_matrix_3x3(double res[3][3], double a[3][3], double b[3][3]);

void	multiply_matrix_4x4(double res[4][4], double a[4][4], double b[4][4]);

/**
 * @brief Calculates the projection of a point.
 *
 * This function takes the coordinates x and y of a point in the map. With
 * the associated z, it calculate the position of this 3D point on a 2D screen
 * according to the camera position. Depending on the user choices, it can also
 * apply the perspective matrix.
 * 
 * The function have no return because it directly save the projected point in
 * a list in the env variable.
 *
 * @param x The x-coordinate of the point in the map.
 * @param y The y-coordinate of the point in the map.
 * @param env The environment variable
 */
void	calculate_point_projection(int x, int y, t_env *env, const t_calc_trigo trigo_calcs);

/**
 * @brief Get the color defined for a point
 * 
 * Depending on the color preset selected and the height of the actual point,
 * a custom color will be returned
 * 
 * @return The actual color
 */
int		get_color_by_preset(t_env *env, int x, int y);

/*╔══════════════════════════════════════════════════════════════════════════╗*/
/*║                                  CAMERA                                  ║*/
/*╚══════════════════════════════════════════════════════════════════════════╝*/

/**
 * @brief Calculate the camera projection.
 *
 * This function calculates the camera's projected coordinates based on its
 * current focus point position and orientation.
 *
 * @param env The environment structure containing every info.
 * @param camera The camera structure to update the projection for.
 */
void	calc_cam_proj(t_env *env, t_camera *camera);

/**
 * @brief Calculate the local axes based on yaw, pitch, and roll.
 *
 * This function initializes the local axes matrix based on the given yaw,
 * pitch, and roll angles.
 * 
 * There is no return to this function because it directly change the axes
 * double tab.
 *
 * @param axes The resulting 3x3 matrix representing the local axes.
 * @param yaw The yaw angle.
 * @param pitch The pitch angle.
 * @param roll The roll angle.
 */
void	get_local_axes(double axes[3][3], t_calc_trigo trigo, t_env *env);

/**
 * @brief Calculate the scale factor for the map.
 *
 * This function calculates the scale factor for rendering the map based on
 * the camera's distance and the map's dimensions.
 *
 * @param map The map structure containing the map dimensions.
 * @param camera The camera structure containing the distance.
 * 
 * @return The calculated scale factor.
 */
double	calc_scale(t_map *map, t_camera *camera);

/**
 * @brief Zoom the camera in or out.
 *
 * This function adjusts the camera's distance based on the zoom direction
 * and recalculates the camera's projection and scale.
 *
 * @param env The environment structure containing the camera.
 * @param direction The direction of the zoom (SCROLL_UP or SCROLL_DOWN).
 */
void	zoom(t_env *env, int direction);

/**
 * @brief Rotate the camera based on mouse movement.
 *
 * This function updates the camera's yaw and pitch based on the mouse
 * movement and recalculates the camera's projection.
 *
 * @param x The current x-coordinate of the mouse.
 * @param y The current y-coordinate of the mouse.
 * @param env The environment structure containing the camera.
 */
void	rotate(int x, int y, t_env *env);

/**
 * @brief Translate the camera based on mouse movement.
 *
 * This function updates the camera's position based on the mouse movement
 * and recalculates the camera's projection.
 *
 * @param x The current x-coordinate of the mouse.
 * @param y The current y-coordinate of the mouse.
 * @param env The environment structure containing the camera.
 */
void	translate(int x, int y, t_env *env);

/**
 * @brief Roll the camera around its forward axis.
 *
 * This function updates the camera's roll angle based on the direction and
 * recalculates the camera's projection.
 *
 * @param direction The direction of the roll.
 * @param env The environment structure containing the camera.
 */
void	roll(int direction, t_env *env);

/**
 * @brief Move the camera based on keyboard input.
 *
 * This function updates the camera's position based on the key pressed and
 * recalculates the camera's projection.
 *
 * @param key The key pressed (KEY_W, KEY_A, KEY_S, KEY_D, KEY_SHIFT, or
 *            KEY_SPACE).
 * @param env The environment structure containing the camera.
 */
void	wasd_move(int key, t_env *env);

/*╔══════════════════════════════════════════════════════════════════════════╗*/
/*║                                  EVENTS                                  ║*/
/*╚══════════════════════════════════════════════════════════════════════════╝*/

/**
 * @brief Handle mouse button press events.
 *
 * This function updates the environment's mouse state based on the button
 * pressed and the mouse coordinates. It also handles zooming.
 *
 * @param button The mouse button pressed.
 * @param x The x-coordinate of the mouse.
 * @param y The y-coordinate of the mouse.
 * @param param The environment variable.
 * 
 * @return Always returns 0.
 */
int		mouse_down(int button, int x, int y, void *param);

/**
 * @brief Handle mouse button release events.
 *
 * This function updates the environment's mouse state based on the button
 * released and the mouse coordinates.
 *
 * @param button The mouse button released.
 * @param x The x-coordinate of the mouse.
 * @param y The y-coordinate of the mouse.
 * @param param The environment variable.
 * 
 * @return Always returns 0.
 */
int		mouse_up(int button, int x, int y, void *param);

/**
 * @brief Handle mouse movement events.
 *
 * This function updates the environment's mouse state based on the mouse
 * coordinates and handles rotation and translation.
 *
 * @param x The x-coordinate of the mouse.
 * @param y The y-coordinate of the mouse.
 * @param param The environment variable.
 * 
 * @return Always returns 0.
 */
int		mouse_move(int x, int y, void *param);

/**
 * @brief Handle camera movement based on keyboard input.
 *
 * This function updates the camera's position and orientation based on the
 * key pressed.
 *
 * @param keycode The key pressed.
 * @param env The environment structure containing the camera.
 */
void	cam_keys(int keycode, t_env *env);

/**
 * @brief Handle the destruction of the environment.
 *
 * This function ends the MLX loop and performs cleanup when the environment
 * is destroyed.
 *
 * @param param The environment variable.
 * 
 * @return Always returns 0.
 */
int		destroy(void *param);

/**
 * @brief Set up event hooks for the environment.
 *
 * This function sets up the necessary event hooks for handling mouse and
 * keyboard events in the environment.
 *
 * @param env The environment structure containing the MLX window.
 */
void	events(t_env *env);

/*╔══════════════════════════════════════════════════════════════════════════╗*/
/*║                                 RENDERING                                ║*/
/*╚══════════════════════════════════════════════════════════════════════════╝*/

/**
 * @brief Put a pixel in the image.
 *
 * This function sets the color of a pixel at the specified coordinates in the
 * image.
 *
 * @param str The image data string.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param color The color of the pixel.
 */
void	put_pixel_image(char *str, int x, int y, int color);

/**
 * @brief Put a pixel in the image if it is in front of the last one.
 *
 * This function sets the color of a pixel at the specified coordinates in the
 * image. If there is alredy a pixel, it will only replace it if it's depth is
 * smaller.
 *
 * @param str The image data string.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param color The color of the pixel.
 * @param depth The depth of the pixel.
 */
void	put_pixel_z_ordered(t_env *env, int x, int y, int color, double depth);

/**
 * @brief Calculate the gradient color between two points.
 *
 * This function calculates the gradient color between two points based on the
 * given ratio.
 *
 * @param point_a The first point.
 * @param point_b The second point.
 * @param ratio The ratio for the gradient calculation.
 * 
 * @return The calculated gradient color.
 */
int		calc_gradiant_point(t_point *point_a, t_point *point_b, double ratio);

/**
 * @brief Calculate the gradient color between two colors.
 *
 * This function calculates the gradient color between two colors based on the
 * given ratio.
 *
 * @param color_a The first color.
 * @param color_b The second color.
 * @param ratio The ratio for the gradient calculation.
 * 
 * @return The calculated gradient color.
 */
int		calc_gradiant_color(int color_a, int color_b, double ratio);

/**
 * @brief Check if a point is within the frame.
 *
 * This function checks if the given point is within the frame boundaries.
 *
 * @param point The point to check.
 * 
 * @return 1 if the point is within the frame, 0 otherwise.
 */
int		is_point_in_frame(t_point point);

/**
 * @brief Draw a line between two points.
 *
 * This function draws a line between two points in the environment.
 *
 * @param point_a The starting point of the line.
 * @param point_b The ending point of the line.
 * @param env The environment structure.
 */
void	draw_line(t_point *point_a, t_point *point_b, t_env *env);

/**
 * @brief Draw all lines in the environment.
 *
 * This function draws all lines stored in the environment.
 *
 * @param env The environment structure.
 */
void	draw_every_lines(t_env *env);

/**
 * @brief Save lines in the environment.
 *
 * This function saves the lines in the environment based on the calculated
 * projection of each point.
 *
 * @param env The environment structure.
 */
void	save_lines(t_env *env);

/**
 * @brief Check if a line is valid.
 *
 * This function checks if a line between two points is valid based on
 * given settings.
 *
 * @param env The environment structure.
 * @param point_a The starting point of the line.
 * @param point_b The ending point of the line.
 * 
 * @return 1 if the line is valid, 0 otherwise.
 */
int		is_valid_line(t_env *env, t_point *point_a, t_point *point_b);

/**
 * @brief Sort lines using quicksort.
 *
 * This function sorts the lines in the environment using the quicksort
 * algorithm.
 *
 * @param lines The array of lines to sort.
 * @param low The starting index.
 * @param high The ending index.
 * @param order The order of sorting (0 for descending, 1 for ascending).
 */
void	quicksort_lines(t_line *lines, int low, int high, int order);

/**
 * @brief Draw a string in the image.
 *
 * This function draws a string in the image using the specified font and
 * starting position.
 * 
 * The difference between this function and the original one of the mlx is
 * that this one draw on an image and not a window so we can gain some
 * efficiency and be sure that there can't be other error.
 *
 * @param img The image structure.
 * @param font The font data.
 * @param p The starting position and color.
 * @param str The string to draw.
 */
void	string_to_img(t_img *img, unsigned char font[96][5], t_point p, char *str);

int		string_size(char *str);

/**
 * @brief Draw a character in the image.
 *
 * This function draws a character in the image using the specified font and
 * starting position.
 * 
 * This function really do the job of string_to_img. Take a character of the
 * font and set the according pixels to a given color
 *
 * @param img The image structure.
 * @param font The font data.
 * @param p The starting position and color.
 * @param c The character to draw.
 */
void	char_to_img(t_img *img, unsigned char font[96][5], t_point p, char c);

/**
 * @brief Initialize the font in the environment.
 *
 * This function initializes the font data in the environment.
 * This function shouldn't be there and the shitty composition of it is due to
 * norm restriction. This really cool norm don't let us define big variable
 * (like the font here) so I have to declare it in two function and join them.
 *
 * @param env The environment structure.
 */
void	init_font(t_env *env);

/**
 * @brief Render a frame in the environment.
 *
 * This function renders a frame in the environment by calculating projections,
 * saving lines, and drawing them.
 *
 * @param env The environment structure.
 */
void	render_frame(t_env *env);

void	extract_frustum_planes(t_frustum *frustum, double matrix[4][4]);
int		is_point_in_frustum(const t_frustum *frustum, const t_vec3 *point);
void	init_view_matrix(double view[4][4], const double axes[3][3], t_env *env);

// Lines
void	draw_line_wu(t_point *point_a, t_point *point_b, t_env *env);
void	draw_line(t_point *point_a, t_point *point_b, t_env *env);
void	draw_line_bresenham(t_point *point_a, t_point *point_b, t_env *env);
void	circle_bres(int xc, int yc, int r, t_env *env, int color);
void	circle_bres_comp(int xc, int yc, int r, t_img *img, int color);
void	draw_rectangle(t_env *env, int start_X, int start_y, int stop_x, int stop_y);
void	draw_filled_circle(int xc, int yc, int r, t_img *img, int color);

// Threads
void	*thread_calc_projection(void *param);

// change point height / draw
void	save_point_at_mouse(t_env *env);
void	edit_point(int key, t_env *env);
void	mouse_up_select(t_env *env);
void	paint_area(t_env *env, int x, int y);
void	change_brush_color(void *color);
void	change_brush_mode(void *color);

// components
int		init_buttons(t_env *env);
void	init_slider(t_env *env);
void	init_text_input(t_env *env);

// Save
void	save_map(const char *filename, t_env *env);
void    save_map_button(void *param);

// procedural map
int		generate_perlin_noise(t_perlin_noise *perlin);
void	clean_perlin(t_perlin_noise *perlin);
t_map	*procedural_map(t_env *env, int argc, char **argv);


#endif