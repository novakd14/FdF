/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:01:09 by dnovak            #+#    #+#             */
/*   Updated: 2024/10/30 15:08:25 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_put_pixel_to_image(int x, int y, int color, t_display *disp)
{
	int	offset;
	int	check_endian;
	int	byte;

	offset = disp->img_prop.size_line * y + disp->img_prop.bpp * x / 8;
	check_endian = 1;
	if (disp->img_prop.endian != *((char *)&check_endian))
		*((int *)(disp->data + offset)) = color;
	else
	{
		byte = 0;
		while (byte < disp->img_prop.bpp / 8)
		{
			*(disp->data + offset + byte) = *((char *)&color
					+ ((disp->img_prop.bpp / 8 - 1) - byte));
			byte++;
		}
	}
}

static void	ft_put_x_line(t_point *pnt_min, t_point *pnt_max, t_display *disp)
{
	double_t	x_curr;
	double_t	y_curr;
	double_t	color;

	x_curr = pnt_min->x;
	while (x_curr < (int)(pnt_max->x))
	{
		y_curr = (pnt_max->y - pnt_min->y) / (pnt_max->x - pnt_min->x) * (x_curr
				- pnt_min->x) + pnt_min->y;
		if (pnt_min->color == pnt_max->color)
			color = pnt_min->color;
		else
			color = (pnt_min->color * (pnt_max->x - x_curr) + pnt_max->color
					* (x_curr - pnt_min->x)) / (pnt_max->x - pnt_min->x);
		ft_put_pixel_to_image((int)x_curr, (int)y_curr, (int)color, disp);
		x_curr++;
	}
}

static void	ft_put_y_line(t_point *pnt_min, t_point *pnt_max, t_display *disp)
{
	double_t	y_curr;
	double_t	x_curr;
	double_t	color;

	y_curr = pnt_min->y;
	while (y_curr < (int)(pnt_max->y))
	{
		x_curr = (pnt_max->x - pnt_min->x) / (pnt_max->y - pnt_min->y) * (y_curr
				- pnt_min->y) + pnt_min->x;
		color = (pnt_min->color * (pnt_max->y - y_curr) + pnt_max->color
				* (y_curr - pnt_min->y)) / (pnt_max->y - pnt_min->y);
		ft_put_pixel_to_image((int)x_curr, (int)y_curr, (int)color, disp);
		y_curr++;
	}
}

static void	ft_put_line_to_image(t_point *point_a, t_point *point_b,
		t_display *disp)
{
	int	x_range;
	int	y_range;

	x_range = (int)ft_abs((long)point_a->x - (long)point_b->x);
	y_range = (int)ft_abs((long)point_a->y - (long)point_b->y);
	if (x_range > y_range)
	{
		if (point_a->x < point_b->x)
			ft_put_x_line(point_a, point_b, disp);
		else
			ft_put_x_line(point_b, point_a, disp);
	}
	else
	{
		if (point_a->y < point_b->y)
			ft_put_y_line(point_a, point_b, disp);
		else
			ft_put_y_line(point_b, point_a, disp);
	}
}

void	ft_put_map_to_image(t_map *map, t_display *disp)
{
	int	o;
	int	a;

	o = 0;
	while (o < map->prop.ordinate)
	{
		a = 0;
		while (a < map->prop.abscissa)
		{
			if (a + 1 < map->prop.abscissa)
				ft_put_line_to_image(&((map->points)[o][a]),
					&((map->points)[o][a + 1]), disp);
			if (o + 1 < map->prop.ordinate)
				ft_put_line_to_image(&((map->points)[o][a]), &((map->points)[o
						+ 1][a]), disp);
			a++;
		}
		o++;
	}
}
