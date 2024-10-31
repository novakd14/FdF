/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:30:44 by dnovak            #+#    #+#             */
/*   Updated: 2024/10/31 11:56:36 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	on_expose(void *param)
{
	t_map		*map;
	t_display	*disp;

	map = ((t_fdf *)param)->map;
	disp = ((t_fdf *)param)->disp;
	set_scale(map, disp);
	scale_projection(map, disp);
	mlx_put_image_to_window(disp->mlx_ptr, disp->win_ptr, disp->img_ptr,
		disp->img_prop.x_offset, disp->img_prop.y_offset);
	return (1);
}

int	on_key(int keycode, void *param)
{
	t_map		*map;
	t_display	*disp;

	map = ((t_fdf *)param)->map;
	disp = ((t_fdf *)param)->disp;
	if (keycode == ESCAPE_KEY)
	{
		free_map(map);
		end_session(disp);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == 'a' || keycode == 'd')
		rotate_image(keycode, map, disp);
	else if (keycode >= 0xFF51 && keycode <= 0xFF54)
		translate_image(keycode, map, disp);
	else if (keycode == 'w' || keycode == 's')
		scale_image(keycode, map, disp);
	return (1);
}

int	on_destroy(void *param)
{
	t_map		*map;
	t_display	*disp;

	map = ((t_fdf *)param)->map;
	disp = ((t_fdf *)param)->disp;
	free_map(map);
	end_session(disp);
	exit(EXIT_SUCCESS);
	return (1);
}

int	on_mouse(int button, int x, int y, void *param)
{
	t_map		*map;
	t_display	*disp;

	map = ((t_fdf *)param)->map;
	disp = ((t_fdf *)param)->disp;
	if (button == 0x4 || button == 0x5)
		mouse_scale_image(button, map, disp);
	return (1);
	(void)x;
	(void)y;
}

void	setup_events(t_fdf *fdf)
{
	mlx_expose_hook(fdf->disp->win_ptr, &on_expose, fdf);
	mlx_key_hook(fdf->disp->win_ptr, &on_key, fdf);
	mlx_mouse_hook(fdf->disp->win_ptr, &on_mouse, fdf);
	mlx_hook(fdf->disp->win_ptr, 17, 0, &on_destroy, fdf);
}
