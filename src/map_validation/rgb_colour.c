/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_colour.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:47:53 by yoonslee          #+#    #+#             */
/*   Updated: 2023/10/26 19:22:09 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map_validation.h"

/// @brief Turns texture_file.png into image using mlx library
/// @param ray
/// @param file_path cub struct param that hs the file path prsed from
/// configuration file
/// @param cub
/// @return new created img struct
t_tex_img	*get_new_xpm_img(t_ray *ray, char *file_path, t_cub *cub)
{
	t_tex_img	*img;

	img = (t_tex_img *)ft_calloc(1, sizeof(t_tex_img));
	if (!img)
		mlx_exit(ray, cub, "Error allocating memory for textures!\n", 1);
	img->img_ptr = mlx_xpm_file_to_image(ray->cbd->mlx, file_path, \
		&(img->width), &(img->height));
	if (!img->img_ptr)
		mlx_exit(ray, cub, "Error creating MLX image pointer!\n", 1);
	img->img_addr = mlx_get_data_addr(img->img_ptr, &(img->bpp), \
		&(img->line_length), &(img->endian));
	if (!img->img_addr)
		mlx_exit(ray, cub, "Error creating MLX image addres!\n", 1);
	return (img);
}

/* init no, so, we, ea t_tex_img struct separately calling another function. */
void	init_textures(t_cub *cub, t_ray *ray)
{
	ray->data->texture[NO] = get_new_xpm_img(ray, cub->no, cub);
	ray->data->texture[SO] = get_new_xpm_img(ray, cub->so, cub);
	ray->data->texture[WE] = get_new_xpm_img(ray, cub->we, cub);
	ray->data->texture[EA] = get_new_xpm_img(ray, cub->ea, cub);
}

/// @brief turns rgb values into unsigned integer values
/// @param arr rgb values from F or C element line (ex. 20,20,20)
/// @return single unsigned integer value of the respective rgb value
static unsigned int	rgb_colour(int *arr)
{
	unsigned int	colour;

	colour = ((arr[0] & 0xff) << 16) + ((arr[1] & 0xff) << 8) + (arr[2] & 0xff);
	return (colour);
}

/// @brief parses the given rgb values
/// @param colour rgb values from F or C element line (ex. 20,20,20)
/// @return single unsigned integer value of the respective rgb value
unsigned int	change_colour(char *colour)
{
	int				*colour_arr;
	char			**colour_str;
	unsigned int	rgb;

	colour_str = ft_split(colour, ',');
	colour_arr = ft_calloc(3, sizeof(int));
	colour_arr[0] = ft_atoi(colour_str[0]);
	colour_arr[1] = ft_atoi(colour_str[1]);
	colour_arr[2] = ft_atoi(colour_str[2]);
	rgb = rgb_colour(colour_arr);
	free(colour_arr);
	free_char_array(colour_str);
	return (rgb);
}
