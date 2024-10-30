/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:48:21 by dnovak            #+#    #+#             */
/*   Updated: 2024/10/24 15:21:02 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_map(t_map *map)
{
	int	o;

	o = 0;
	while (o < map->prop.ordinate)
		free(map->points[o++]);
	free(map->points);
}

void	free_split_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		free(array[i++]);
	free(array);
}

void	free_all(t_map *map, char **split, int fd)
{
	if (map->points != NULL)
		free_map(map);
	if (split != NULL)
		free_split_array(split);
	if (fd >= 0)
		close(fd);
}

void	end_session(t_display *disp)
{
	if (disp->img_ptr != NULL)
		mlx_destroy_image(disp->mlx_ptr, disp->img_ptr);
	if (disp->win_ptr != NULL)
		mlx_destroy_window(disp->mlx_ptr, disp->win_ptr);
	if (disp->mlx_ptr != NULL)
	{
		mlx_destroy_display(disp->mlx_ptr);
		free(disp->mlx_ptr);
	}
}
