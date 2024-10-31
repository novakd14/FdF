/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:46:34 by dnovak            #+#    #+#             */
/*   Updated: 2024/10/31 14:47:01 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	mouse_scale_image(int button, t_map *map, t_display *disp)
{
	if (button == 0x4)
		map->prop.scale += map->prop.scale_unit;
	else if (button == 0x5)
		map->prop.scale -= map->prop.scale_unit;
	else
		return ;
	setup_projection(map);
	scale_projection(map, disp);
	clear_image(disp);
	ft_put_map_to_image(map, disp);
	mlx_clear_window(disp->mlx_ptr, disp->win_ptr);
	mlx_put_image_to_window(disp->mlx_ptr, disp->win_ptr, disp->img_ptr,
		disp->img_prop.x_offset, disp->img_prop.y_offset);
}
