
#ifndef RAY_CASTING_H
# define RAY_CASTING_H

# define FOV 60
# define K_ESC 53

# include "cub3d.h"

typedef struct s_data	t_data;
typedef struct s_cub	t_cub;
typedef struct s_cbd	t_cbd;

typedef struct s_ray
{
	float			pa;
	float			ra; //ray angle starting position
	float			rai; //ray angle iteration
	struct s_data	*data;
	struct s_cbd	*cbd;
	// struct s_cub	*cub;
}	t_ray;

// draw_image.c
void	draw_player(t_cbd *cbd, t_ray *ray);
void	draw_image(t_cbd *cbd, t_ray *ray);

// hooks.c
void	set_hooks(t_cbd *cbd);

// mlx_utils.c
void	my_mlx_pixel_put(t_cbd *cbd, int x, int y, int color);
int		destroy_flag(t_cbd *cbd, int flag);
int		destroy(t_cbd *cbd);

// ray_casting_utils.c
float	fix_angle(float a);
float	deg_to_rad(float a);
void	player_orientation_to_angle(t_data *mv, t_ray *ray);

// render.c
void	draw_background(t_cbd *cbd);
void	render_image(t_cbd *cbd, t_ray *ray);
void	init_render_utils(t_cbd *cbd, t_data *mv);

#endif
