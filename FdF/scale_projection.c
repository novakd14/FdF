/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_projection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 04:30:22 by dnovak            #+#    #+#             */
/*   Updated: 2024/10/31 11:46:00 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_scale(t_map *map, t_display *disp)
{
	if (disp->x_size / map->prop.x_size < disp->y_size / map->prop.y_size)
		map->prop.scale = disp->x_size / map->prop.x_size * 0.64;
	else
		map->prop.scale = disp->y_size / map->prop.y_size * 0.64;
}

void	scale_projection(t_map *map, t_display *disp)
{
	int	o;
	int	a;

	o = 0;
	while (o < map->prop.ordinate)
	{
		a = 0;
		while (a < map->prop.abscissa)
		{
			map->points[o][a].x = map->points[o][a].x_orig
				* map->prop.scale;
			map->points[o][a].y = map->points[o][a].y_orig
				* map->prop.scale;
			map->points[o][a].x += disp->x_size * 0.4 + map->prop.x_offset;
			map->points[o][a].y += disp->y_size * 0.4 + map->prop.y_offset;
			a++;
		}
		o++;
	}
}
