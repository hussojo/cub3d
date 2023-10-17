/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_mini_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:19:46 by yoonslee          #+#    #+#             */
/*   Updated: 2023/10/17 15:23:44 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"
#include "../../include/cub3d.h"
#include "../../include/map_validation.h"

/**
 * @brief draw player on the minimap
 */
void	draw_player(t_cbd *cbd, t_ray *ray)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < 5)
	{
		y = 0;
		while (y < 5)
		{
			my_mlx_pixel_put(cbd, x + ((ray->pix_x_pos / 4) - 2), \
			y + ((ray->pix_y_pos / 4) - 2), PINK);
			y++;
		}
		x++;
	}
}

/**
 * @brief draw grid of the minimap so it is easier for the player to see
 *  the angle of the views
 */
static void	draw_grid(t_cbd *cbd, t_data *mv)
{
	int	x;
	int	y;

	x = 0;
	while (x < mv->width * MINI_PIX)
	{
		y = -1;
		while (++y < mv->height * MINI_PIX)
			my_mlx_pixel_put(cbd, x, y, BLACK);
		x = x + MINI_PIX;
	}
	x = -1;
	while (++x < mv->width * MINI_PIX)
	{
		y = 0;
		while (y < mv->height * MINI_PIX)
		{
			my_mlx_pixel_put(cbd, x, y, BLACK);
			y = y + MINI_PIX;
		}
	}
}

/**
 * @brief draw minimap's wall and path based on 
 */
static void	draw_map(t_cbd *cbd, int x, int y, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < MINI_PIX)
	{
		j = -1;
		while (++j < MINI_PIX)
		{
			my_mlx_pixel_put(cbd, x + i, y + j, color);
		}
	}
}

static int	p_pos(char c)
{
	if (c == 'W' || c == 'E' || c == 'S' || c == 'N')
		return (1);
	else
		return (0);
}

static void	fill_map(t_data *mv)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (mv->map[i])
	{
		if ((int)ft_strlen(mv->map[i]) < mv->width)
		{
			temp = fill_temp(mv, mv->map, temp, i);
			free(mv->map[i]);
			mv->map[i] = ft_strdup(temp);
			free(temp);
		}
		i++;
	}
}

/**
 * @brief make minimap for the cub3D bonus part.
 * draws the preview of the map on the corner of the screen
 */
void	make_mini_map(t_cbd *cbd, t_data *mv)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	fill_map(mv);
	print_map(mv->map);
	while (i < mv->height)
	{
		j = 0;
		while (j < mv->width)
		{
			if (mv->map[i][j] == '1')
				color = BLUE;
			else if (mv->map[i][j] == '0' || p_pos(mv->map[i][j]))
				color = LIGHTBLUE;
			else
				color = BLACK;
			draw_map(cbd, j * MINI_PIX, i * MINI_PIX, color);
			j++;
		}
		i++;
	}
	draw_grid(cbd, mv);
}
