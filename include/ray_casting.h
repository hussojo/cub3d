
#ifndef RAY_CASTING_H
# define RAY_CASTING_H

# define FOV 60
# define GRID_PIX 24
# define K_ESC 53
# define ANGLE 5
# define SPEED 5
# define PLAYER_S 5
// # define NOSE_LEN 1

# define BLACK 0x000000
# define WHITE 0xffffff
# define GREEN 0x009933
# define OLIVE 0x808000
# define KHAKI 0xE519EFC
# define GREY 0x808080
# define LIGHTBLUE 0xADD8E6
# define BLUE 0x4169e1

# include "cub3d.h"

typedef struct s_data	t_data;
typedef struct s_cub	t_cub;
typedef struct s_cbd	t_cbd;
typedef struct s_line	t_line;

typedef struct s_vector
{
	float	x;
	float	y;
	float	pa;
}	t_vector;

/**
 * @param x0 line starting x position
 * @param y0 line starting y position
 * @param x1 line ending x
 * @param y1 line ending y
 * @param dx absolute difference between x0 and x1
 * @param dy absolute difference between y0 and y1
 * @param sx sign of x -> sx = 1 if x1 > x0 | sx = -1 if x1 < x0
 * @param sy sign of y -> sy = 1 if y1 > y0 | sy = -1 if y1 < y0
*/
typedef	struct s_line
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	error;
	int	error2;
}	t_line;

/**
 * @param pa angle of the player Degrees
 * @param ra ray angle starting position
 * @param rai ray angle iteration
 * @param cotan line length(cotan)
 * @param center_x center of the window_width
 * @param center_y center of the window_height
 * @param xo x's offset
 * @param yo y's offset
 * @param pix_x_pos player's x position in pixel
 * @param pix_y_pos player's y position in pixel
 */
typedef struct s_ray
{
	float			pa;
	float			ra;
	float			rai;
	float			cotan;
	float			center_width;
	float			center_height;
	float			pix_x_pos;
	float			pix_y_pos;
	float			ray_x;
	float			ray_y;
	float			xo;
	float			yo;
	float			pdx;
	float			pdy;
	struct s_data	*data;
	struct s_cbd	*cbd;
	struct s_vector	*vector;
	struct s_line	*line;
	// struct s_cub	*cub;
}	t_ray;



// draw_image.c
// void	draw_image(t_cbd *cbd, t_ray *ray);

// hooks.c
void	set_hooks(t_cbd *cbd, t_ray *ray);

// line_drawing_utils.c
void	bresenham(t_ray *ray);
void	draw_nose(t_ray *ray);

// mlx_utils.c
void	my_mlx_pixel_put(t_cbd *cbd, int x, int y, int color);
int		destroy_flag(t_cbd *cbd, int flag);
int		destroy(t_cbd *cbd);

// ray_casting_utils.c
float	fix_angle(float a);
float	deg_to_rad(float a);
void	player_orientation_to_angle(t_data *mv, t_ray *ray);

// render.c
// void	draw_background(t_cbd *cbd);
void	render_image(t_cbd *cbd, t_ray *ray, t_data *mv);
void	init_render_utils(t_cbd *cbd, t_data *mv);

//making_map.c
void	make_map(t_cbd *cbd, t_data *mv);
void	draw_player(t_cbd *cbd, t_ray *ray);

//movement.c
void	move_frontback(t_ray *ray, char *direction);
void	move_sideway(t_ray *ray, char *direction);

//draw_background.c
void	draw_background(t_ray *ray);

#endif
