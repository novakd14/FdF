/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_projection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:56:50 by dnovak            #+#    #+#             */
/*   Updated: 2024/10/31 14:38:24 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	choose_projection(int o, int a, t_map *map)
{
	if (map->prop.projection == ISOMETRIC)
		isometric_projection(o, a, &(map->points)[o][a], map->prop.rotate);
	else
		cabinet_projection(o, a, &(map->points)[o][a], map->prop.rotate);
}

static void	init_map_borders(t_point *point, t_map *map)
{
	map->prop.x_min = point->x_orig;
	map->prop.x_max = point->x_orig;
	map->prop.y_min = point->y_orig;
	map->prop.y_max = point->y_orig;
}

static void	find_map_borders(t_point *point, t_map *map)
{
	if (map->prop.x_min > point->x_orig)
		map->prop.x_min = point->x_orig;
	if (map->prop.x_max < point->x_orig)
		map->prop.x_max = point->x_orig;
	if (map->prop.y_min > point->y_orig)
		map->prop.y_min = point->y_orig;
	if (map->prop.y_max < point->y_orig)
		map->prop.y_max = point->y_orig;
}

static void	center_projection(t_map *map)
{
	int	o;
	int	a;

	o = 0;
	while (o < map->prop.ordinate)
	{
		a = 0;
		while (a < map->prop.abscissa)
		{
			map->points[o][a].x_orig = map->points[o][a].x_orig
				- (map->prop.x_max + map->prop.x_min) / 2.;
			map->points[o][a].y_orig = map->points[o][a].y_orig
				- (map->prop.y_max + map->prop.y_min) / 2.;
			a++;
		}
		o++;
	}
}

void	setup_projection(t_map *map)
{
	int	o;
	int	a;

	o = 0;
	while (o < map->prop.ordinate)
	{
		a = 0;
		while (a < map->prop.abscissa)
		{
			choose_projection(o, a, map);
			if (o == 0 && a == 0)
				init_map_borders(&(map->points)[0][0], map);
			else
				find_map_borders(&(map->points)[o][a], map);
			a++;
		}
		o++;
	}
	center_projection(map);
	map->prop.x_size = map->prop.x_max - map->prop.x_min;
	map->prop.y_size = map->prop.y_max - map->prop.y_min;
}
