/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:12:04 by dnovak            #+#    #+#             */
/*   Updated: 2024/10/31 11:19:30 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_pointers(t_display *disp, t_map *map)
{
	disp->mlx_ptr = mlx_init();
	if (disp->mlx_ptr == NULL)
	{
		free_map(map);
		exit_message(EXIT_FAILURE, "Failed to set up connection.\n");
	}
	mlx_get_screen_size(disp->mlx_ptr, &disp->x_size, &disp->y_size);
	disp->win_ptr = mlx_new_window(disp->mlx_ptr, disp->x_size * 80 / 100,
			disp->y_size * 80 / 100, "Fdf");
	if (disp->win_ptr == NULL)
	{
		free_map(map);
		end_session(disp);
		exit_message(EXIT_FAILURE, "Failed to create window.\n");
	}
	disp->img_ptr = mlx_new_image(disp->mlx_ptr, disp->x_size, disp->y_size);
	if (disp->img_ptr == NULL)
	{
		free_map(map);
		end_session(disp);
		exit_message(EXIT_FAILURE, "Failed to create image.\n");
	}
}

static void	init_data(t_display *disp, t_map *map)
{
	disp->data = mlx_get_data_addr(disp->img_ptr, &(disp->img_prop.bpp),
			&(disp->img_prop.size_line), &(disp->img_prop.endian));
	if (disp->data == NULL)
	{
		free_map(map);
		end_session(disp);
		exit_message(EXIT_FAILURE, "Failed to retriev image data.\n");
	}
}

void	setup_display(t_display *disp, t_map *map)
{
	init_pointers(disp, map);
	init_data(disp, map);
}

void	clear_image(t_display *disp)
{
	ft_bzero(disp->data, disp->img_prop.size_line * disp->y_size);
}
