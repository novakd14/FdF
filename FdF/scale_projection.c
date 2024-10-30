/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_projection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 04:30:22 by dnovak            #+#    #+#             */
/*   Updated: 2024/10/30 04:30:49 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_scale(t_map *map, t_display *disp)
{
	if (disp->x_size / map->prop.x_size < disp->y_size / map->prop.y_size)
		disp->img_prop.scale = disp->x_size / map->prop.x_size;
	else
		disp->img_prop.scale = disp->y_size / map->prop.y_size;
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
				* disp->img_prop.scale * 0.8;
			map->points[o][a].y = map->points[o][a].y_orig
				* disp->img_prop.scale * 0.8;
			map->points[o][a].x += disp->x_size / 2;
			map->points[o][a].y += disp->y_size / 2;
			a++;
		}
		o++;
	}
}
