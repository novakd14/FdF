/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:55:03 by dnovak            #+#    #+#             */
/*   Updated: 2024/10/22 11:17:44 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	print_key(int keycode, void *param)
{
	ft_printf("Pressed: %i\n", keycode);
	if (keycode == ESCAPE_KEY)
	{
		ft_printf("Pressed ESC key, terminating progam.\n");
		exit(EXIT_SUCCESS);
	}
	if (param != NULL)
		ft_printf("There are param.\n");
	return (1);
}

int	print_mouse(int button, int x, int y, void *param)
{
	ft_printf("Pressed: %i (%i,%i)\n", button, x, y);
	if (param != NULL)
		ft_printf("There are param.\n");
	return (1);
}

int	print_expose(void *param)
{
	ft_printf("Exposed\n");
	if (param != NULL)
		ft_printf("There are param.\n");
	return (1);
}

int	loop_hook(void *param)
{
	ft_printf("Loop hook\n");
	if (param != NULL)
		ft_printf("There are param.\n");
	return (1);
}

void	draw_horizontal_line(void *mlx_ptr, void *win_ptr, int x, int y,
		int len)
{
	while (--len >= 0)
		mlx_pixel_put(mlx_ptr, win_ptr, x + len, y, 255);
}

int	main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	if (mlx_ptr == NULL)
	{
		ft_printf("Failed to set up connection. Exiting program.\n");
		return (1);
	}
	ft_printf("Did set up connection.\n");
	win_ptr = mlx_new_window(mlx_ptr, 1000, 500, "Test window");
	draw_horizontal_line(mlx_ptr, win_ptr, 500, 250, 100);
	mlx_key_hook(win_ptr, &print_key, NULL);
	mlx_mouse_hook(win_ptr, &print_mouse, NULL);
	mlx_expose_hook(win_ptr, &print_expose, NULL);
	mlx_loop_hook(win_ptr, &loop_hook, NULL);
	mlx_loop(mlx_ptr);
	return (0);
}
