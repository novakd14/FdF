/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:46:35 by dnovak            #+#    #+#             */
/*   Updated: 2024/10/30 23:59:29 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_point	**create_temp_map(t_map *map)
{
	t_point	**temp_pts;

	temp_pts = (t_point **)calloc(map->prop.ordinate + 1, sizeof(t_point *));
	if (temp_pts == NULL)
		return (NULL);
	temp_pts[map->prop.ordinate] = (t_point *)calloc(map->prop.abscissa,
			sizeof(t_point));
	if (temp_pts[map->prop.ordinate] == NULL)
	{
		free(temp_pts);
		return (NULL);
	}
	return (temp_pts);
}

static void	fill_ordinate(char **split, t_point **temp_pts, t_map *map)
{
	int		a;
	char	*midptr;
	char	*endptr;

	a = 0;
	while (a < map->prop.abscissa)
	{
		temp_pts[map->prop.ordinate][a].alt = ft_strtol(split[a], &midptr, 10);
		if (*midptr == ',')
		{
			temp_pts[map->prop.ordinate][a].color = ft_strtol(midptr + 1,
					&endptr, 0);
			if (midptr + 1 == endptr)
				temp_pts[map->prop.ordinate][a].color = WHITE;
		}
		else
			temp_pts[map->prop.ordinate][a].color = WHITE;
		a++;
	}
}

static void	copy_map(t_map *map, t_point **temp_points)
{
	int	o;

	o = 0;
	while (o < map->prop.ordinate)
	{
		temp_points[o] = map->points[o];
		o++;
	}
}

void	expand_map(t_map *map, char **split, int fd)
{
	t_point	**temp_points;

	temp_points = create_temp_map(map);
	if (temp_points == NULL)
	{
		free_all(map, split, fd);
		exit_message(EXIT_FAILURE, "Could not allocate memory.\n");
	}
	fill_ordinate(split, temp_points, map);
	free_split_array(split);
	copy_map(map, temp_points);
	if (map->points != NULL)
		free(map->points);
	map->points = temp_points;
}
