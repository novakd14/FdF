/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:36:02 by dnovak            #+#    #+#             */
/*   Updated: 2024/10/31 15:04:25 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	isometric_projection(int o, int a, t_point *point, int rotate)
{
	if (rotate == 0)
	{
		point->x_orig = (a - o) * sqrt(3) / 2.;
		point->y_orig = (a + o) / 2. - point->alt;
	}
	else if (rotate == 90)
	{
		point->x_orig = (o + a) * sqrt(3) / 2.;
		point->y_orig = (o - a) / 2. - point->alt;
	}
	else if (rotate == 180)
	{
		point->x_orig = -(a - o) * sqrt(3) / 2.;
		point->y_orig = -(o + a) / 2. - point->alt;
	}
	else
	{
		point->x_orig = -(o + a) * sqrt(3) / 2.;
		point->y_orig = -(o - a) / 2. - point->alt;
	}
}

void	cabinet_projection(int o, int a, t_point *point, int rotate)
{
	if (rotate == 0)
	{
		point->x_orig = a - o * sqrt(2) / 4.;
		point->y_orig = o * sqrt(2) / 4. - point->alt;
	}
	else if (rotate == 90)
	{
		point->x_orig = o + a * sqrt(2) / 4.;
		point->y_orig = -a * sqrt(2) / 4. - point->alt;
	}
	else if (rotate == 180)
	{
		point->x_orig = -a + o * sqrt(2) / 4.;
		point->y_orig = -o * sqrt(2) / 4. - point->alt;
	}
	else
	{
		point->x_orig = -o - a * sqrt(2) / 4.;
		point->y_orig = a * sqrt(2) / 4. - point->alt;
	}
}
