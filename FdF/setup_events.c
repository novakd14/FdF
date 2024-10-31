/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:30:44 by dnovak            #+#    #+#             */
/*   Updated: 2024/10/30 20:34:33 by dnovak           ###   ########.fr       */
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

void	setup_events(t_fdf *fdf)
{
	mlx_expose_hook(fdf->disp->win_ptr, &on_expose, fdf);
	mlx_key_hook(fdf->disp->win_ptr, &on_key, fdf);
	mlx_hook(fdf->disp->win_ptr, 17, 0, &on_destroy, fdf);
}
