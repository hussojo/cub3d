/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:01:42 by jhusso            #+#    #+#             */
/*   Updated: 2023/10/17 15:42:38 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/file_validation.h"

int	all_digits(char *number)
{
	int	i;
	int	len;

	len = ft_strlen(number);
	i = -1;
	while (++i < len)
	{
		if (!ft_isdigit(number[i]))
			return (-1);
	}
	return (0);
}

/// @brief prints out error messagge to stderr and frees cub struct according
/// to flag
/// @param cub
/// @param str error message
/// @param struct_flag if cub struct needs to be freed flag = 1
void	file_print_error(t_cub *cub, char *str, int struct_flag)
{
	ft_putstr_fd(str, 2);
	if (struct_flag == 1)
		free_cub_struct(cub);
	exit(1);
}

/// @brief Checks if the current line is part of the map, by checking the first
/// non whitespace character in the begining of line
/// @param line
/// @return 1 if line belongs to map, 0 if line does not belong to map
int	is_map(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (ft_isdigit(line[i]))
		return (1);
	return (0);
}
