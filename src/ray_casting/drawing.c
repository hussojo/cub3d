/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:33:18 by yoonslee          #+#    #+#             */
/*   Updated: 2023/10/26 19:08:03 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"
#include "../../include/cub3d.h"

/**
 * @brief draw ceiling & floor based on the colour that is given from the map
 */
void	draw_background(t_ray *ray)
{
	int				x;
	int				y;
	unsigned int	color;

	y = 0;
	color = ray->data->ceiling_rgb;
	while (y < WIN_SIZE_Y)
	{
		if (y > WIN_SIZE_Y / 2)
			color = ray->data->floor_rgb;
		x = -1;
		while (++x < WIN_SIZE_X)
		{
			my_mlx_pixel_put(ray->cbd, x, y, color);
		}
		y++;
	}
}

/**
 * @brief finding the location of texture and draw the image
 * 
 * @param PR_PLANE Project plane :(WINDOW_WIDTH / 2) / tan(30degree)
 * @param y_count step size of traversing the image in y axis(top to bottom)
 */
void	draw_image(t_ray *ray, t_line *line)
{
	float	y_count;

	ray->wall_height = (int)(GRID_PIX / ray->distance * (PR_PLANE * 0.75));
	y_count = TEX_PIX / ray->wall_height;
	if (ray->shortest == 'h')
		texture_location(ray, y_count, line->x1, line->y1);
	else
		texture_location(ray, y_count, line->v_x1, line->v_y1);
	texture_wall(ray, ray->ray_count, (int)ray->wall_height, y_count);
}
