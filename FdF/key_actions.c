/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:50:46 by dnovak            #+#    #+#             */
/*   Updated: 2024/10/31 11:53:45 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_image(int keycode, t_map *map, t_display *disp)
{
	if (keycode == 'a')
		map->prop.rotate = (map->prop.rotate + 90) % 360;
	else if (keycode == 'd')
		map->prop.rotate = (map->prop.rotate + 270) % 360;
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

void	translate_image(int keycode, t_map *map, t_display *disp)
{
	if (keycode == 0xFF51)
		map->prop.x_offset -= map->prop.offset_unit;
	else if (keycode == 0xFF53)
		map->prop.x_offset += map->prop.offset_unit;
	else if (keycode == 0xFF52)
		map->prop.y_offset -= map->prop.offset_unit;
	else if (keycode == 0xFF54)
		map->prop.y_offset += map->prop.offset_unit;
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

void	scale_image(int keycode, t_map *map, t_display *disp)
{
	if (keycode == 'w')
		map->prop.scale += map->prop.scale_unit;
	else if (keycode == 's')
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
