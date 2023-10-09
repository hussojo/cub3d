/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 09:40:10 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/09 16:20:07 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray_casting.h"


//we need to do something about when x1 and y1 goes to minus! :)
// void	check_horizontal_gridline(t_ray *ray)
// {
// 	/* finding the first intersection cordinates */
// 	t_line	line;

// 	line.x0 = ray->pix_x_pos;
// 	line.y0 = ray->pix_y_pos;
// 	line.x1 = 0;
// 	line.y1 = 0;
// 	printf("ray->pa: %f\n", ray->pa);
// 	printf("ray->ra: %f\n", ray->ra);
// 	if (ray->ra >= 0 && ray->ra < 181) // going upwards
// 	{
// 		line.y1 = (int)(line.y0) / GRID_PIX * GRID_PIX - 1; //if y1 is part of the block above the grid line needs to add 1?
// 		printf("line x1 value is %f\n", line.x0);
// 		printf("line x1 value is %f\n", (line.y0 - line.y1));
// 		line.x1 = line.x0 + ((line.y0 - line.y1) / tan(deg_to_rad(ray->ra)));
// 		printf("tan(ray->ra) is %f\n", tan(ray->ra));
// 		line.ya = -(GRID_PIX);
// 	}
// 	else if (ray->ra > 180 && ray->ra <= 360)
// 	{
// 		line.y1 = (int)(line.y0) / GRID_PIX * GRID_PIX + GRID_PIX;
// 		line.x1 = line.x0 + ((line.y0 - line.y1) / tan(deg_to_rad(ray->ra)));
// 		line.ya = GRID_PIX;
// 	}
// 	while (42)
// 	{
// 		printf("line.x1 is %f\n", line.x1);
// 		printf("line.y1 is %f\n", line.y1);
// 		//from the print out, you'll see it segfaults when line.x1 and line.y1 is minus. we need to do something to make sure that it won't go under 0.
// 		line.xa = -line.ya / tan(deg_to_rad(ray->ra));
// 		// if no wall at (x1, y1) increment to new (x1, y1) coordinates
// 		if (is_wall(ray, line.x1 + line.xa, line.y1 + line.ya))  //this is added here so we won't go draw the line if there is wall. But it segfaults after three angle moves.
// 			break ;
// 		line.y1 = (line.y1 + line.ya) / GRID_PIX;
// 		line.x1 = (line.x1 + line.xa) / GRID_PIX;
// 	}
// 	bresenham(ray, &line, BLACK);
// 	// if wall at (x1, y1), return to caller function
// }

void	check_vertical_gridline(t_ray *ray, t_line *line)
{
	int		dof;
	float	disV;

	dof = 0;
	disV = 100000;
	line->x0 = ray->pix_x_pos;
	line->y0 = ray->pix_y_pos;
	line->v_x1 = 0;
	line->v_y1 = 0;
	printf("ray->pa: %f\n", ray->pa);
	printf("ray->ra: %f\n", ray->ra);
	if (cos(deg_to_rad(ray->ra) > 0.001)) //right pointing diagonal line like this /
	{
		line->v_x1 = (int)(line->x0) / GRID_PIX * GRID_PIX + GRID_PIX;
		line->v_y1 = line->y0 + ((line->x0 - line->v_x1) * tan(deg_to_rad(ray->ra)));
		line->v_xa = GRID_PIX;
		line->v_ya = -line->v_xa * tan(deg_to_rad(ray->ra));
	}
	else if (cos(deg_to_rad(ray->ra) < -0.001)) //left pointing diagonal line like this '\'
	{
		line->v_x1 = (int)(line->x0) / GRID_PIX * GRID_PIX - 0.0001;
		line->v_y1 = line->y0 + ((line->x0 - line->v_x1) * tan(deg_to_rad(ray->ra)));
		line->v_xa = -(GRID_PIX);
		line->v_ya = -line->v_xa * tan(deg_to_rad(ray->ra));
	}
	else
	{
		line->v_x1 = line->x0;
		line->v_y1 = line->y0;
	}
	printf("before while loop: line.x1 is %f\n", line->v_x1);
	printf("before while loop: line.y1 is %f\n", line->v_y1);
	while (!is_wall(ray, line->v_x1, line->v_y1))
	{
		printf("do you come here?");
		if ((int)line->v_y1 <= 0 || (int)line->v_y1 >= GRID_PIX * ray->data->height)
			break ;
		line->v_y1 = (line->v_y1 + line->v_ya);
		line->v_x1 = (line->v_x1 + line->v_xa);
	}
	printf("line.x1 is %f\n", line->v_x1);
	printf("line.y1 is %f\n", line->v_y1);
	line->x1 = (int)line->v_x1;
	line->y1 = (int)line->v_y1;
	bresenham(ray, line, BLACK);
}
