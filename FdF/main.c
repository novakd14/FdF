/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:55:03 by dnovak            #+#    #+#             */
/*   Updated: 2024/10/30 05:22:58 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_fdf(t_fdf *fdf, t_map *map, t_display *disp)
{
	fdf->map = map;
	fdf->disp = disp;
}

static void	init_map(t_map *map)
{
	map->points = NULL;
	map->prop.ordinate = 0;
	map->prop.abscissa = 0;
}

static void	init_display(t_display *disp)
{
	disp->mlx_ptr = NULL;
	disp->win_ptr = NULL;
	disp->img_ptr = NULL;
	disp->data = NULL;
	disp->x_size = X_SIZE;
	disp->y_size = Y_SIZE;
}

int	main(int argc, char **argv)
{
	t_fdf		fdf;
	t_map		map;
	t_display	disp;

	if (argc != 2)
		exit_message(EXIT_FAILURE, "Wrong number of arguments.\n");
	init_map(&map);
	load_map(argv[1], &map);
	setup_projection(&map);
	init_display(&disp);
	setup_display(&disp, &map);
	set_scale(&map, &disp);
	scale_projection(&map, &disp);
	ft_put_map_to_image(&map, &disp);
	mlx_put_image_to_window(disp.mlx_ptr, disp.win_ptr, disp.img_ptr, 0, 0);
	init_fdf(&fdf, &map, &disp);
	setup_events(&fdf);
	mlx_loop(disp.mlx_ptr);
	return (EXIT_SUCCESS);
}
