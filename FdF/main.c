/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:55:03 by dnovak            #+#    #+#             */
/*   Updated: 2024/10/24 10:55:11 by dnovak           ###   ########.fr       */
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

void	draw_line(void *mlx_ptr, void *win_ptr, double_t x[2], double_t y[2])
{
	double_t	x_curr;
	double_t	x_max;
	double_t	y_curr;
	double_t	color;

	x_curr = ft_double_min(x[0], x[1]);
	x_max = ft_double_max(x[0], x[1]);
	while (x_curr < x_max)
	{
		y_curr = (y[1] - y[0]) / (x[1] - x[0]) * (x_curr - x[0]) + y[0];
		color = 255 / (x[1] - x[0]) * (x_curr - x[0]);
		mlx_pixel_put(mlx_ptr, win_ptr, (int)x_curr, (int)y_curr, RED * 255
			+ (BLUE + GREEN) * (int)color);
		x_curr++;
	}
}

// Returns length of array of strings, ended with NULL.
int	ft_str_array_len(char **array)
{
	int	len;

	if (array == NULL)
		return (-1);
	len = 0;
	while (array[len] != NULL)
		len++;
	return (len);
}

void	free_split_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		free(array[i++]);
	free(array);
}

void	free_map(t_point **map, int ordinate)
{
	int	o;

	if (map == NULL)
		return ;
	o = 0;
	while (o < ordinate)
		free(map[o++]);
	free(map);
}

void	free_all(t_point **map, int ordinate, char **split, int fd)
{
	if (map != NULL)
		free_map(map, ordinate);
	if (split != NULL)
		free_split_array(split);
	close(fd);
}

void	exit_message(int result, char *message)
{
	if (result == EXIT_FAILURE)
	{
		write(STDERR_FILENO, message, ft_strlen(message));
		exit(EXIT_FAILURE);
	}
	write(STDOUT_FILENO, message, ft_strlen(message));
	exit(EXIT_FAILURE);
}

void	put_map(t_point **map, t_prop *map_prop)
{
	int	o;
	int	a;

	o = 0;
	while (o < map_prop->ordinate)
	{
		a = 0;
		while (a < map_prop->abscissa)
			ft_printf("% 3i", map[o][a++].alt);
		ft_printf("\n");
		o++;
	}
}

int	open_file(char *file_name)
{
	int	len;
	int	fd;

	len = ft_strlen(file_name);
	if (len < 5)
		exit_message(EXIT_FAILURE, "Run program in format: ./fdf *.fdf\n");
	if (ft_strncmp((file_name + len - 4), ".fdf\0", 5) != 0)
		exit_message(EXIT_FAILURE, "Input *.fdf file.\n");
	fd = open(file_name, O_RDONLY); // close(fd)
	if (fd < 0)
		exit_message(EXIT_FAILURE, "Could not open the file.\n");
	return (fd);
}

void	check_split(char **split, t_prop *map_prop, t_point **map)
{
	int	a;

	a = 0;
	while (a < map_prop->abscissa)
	{
		if (!ft_isdigit(*split[a]) && (*split[a] != '-'
				|| !ft_isdigit(*(split[a] + 1))))
		{
			free_map(map, map_prop->ordinate);
			free_split_array(split);
			exit_message(EXIT_FAILURE, "Wrong format of a map.\n");
		}
		a++;
	}
}

void	copy_map(t_point **from, t_point **to, t_prop *map_prop)
{
	int	o;

	o = 0;
	while (o < map_prop->ordinate)
	{
		to[o] = from[o];
		o++;
	}
}

void	fill_ordinate(char **split, t_point **temp_map, t_prop *map_prop)
{
	int	a;

	a = 0;
	while (a < map_prop->abscissa)
	{
		temp_map[map_prop->ordinate][a].alt = ft_atoi(split[a]);
		a++;
	}
}

t_point	**create_temp_map(t_prop *map_prop)
{
	t_point	**temp_map;

	temp_map = (t_point **)calloc(map_prop->ordinate + 1, sizeof(t_point *));
	if (temp_map == NULL)
		return (NULL);
	temp_map[map_prop->ordinate] = (t_point *)calloc(map_prop->abscissa,
			sizeof(t_point));
	if (temp_map[map_prop->ordinate] == NULL)
	{
		free(temp_map);
		return (NULL);
	}
	return (temp_map);
}

t_point	**new_map(t_point **map, t_prop *map_prop, char **split, int fd)
{
	t_point	**temp_map;

	temp_map = create_temp_map(map_prop);
	if (temp_map == NULL)
	{
		free_all(map, map_prop->ordinate, split, fd);
		exit_message(EXIT_FAILURE, "Could not allocate memory.\n");
	}
	fill_ordinate(split, temp_map, map_prop);
	free_split_array(split);
	copy_map(map, temp_map, map_prop);
	free(map);
	return (temp_map);
}

char	*load_first_line(int fd)
{
	char	*line;

	line = get_next_line(fd); // FREE(line)
	if (line == NULL)
	{
		close(fd);
		exit_message(EXIT_FAILURE, "File is empty.\n");
	}
	return (line);
}

t_point	**load_map(char *file_name, t_prop *map_prop)
{
	int		fd;
	char	*line;
	t_point	**map;
	char	**split;

	fd = open_file(file_name); // close(fd)
	line = load_first_line(fd);
	map = NULL;
	while (line != NULL)
	{
		split = ft_split(line, ' '); // FREE(split)
		free(line);
		if (split == NULL)
		{
			close(fd);
			exit_message(EXIT_FAILURE, "Could not allocate memory.\n");
		}
		map_prop->abscissa = ft_str_array_len(split);
		check_split(split, map_prop, map);
		map = new_map(map, map_prop, split, fd);
		map_prop->ordinate++;
		line = get_next_line(fd);
	}
	close(fd);
	return (map);
}

static void	init_map_prop(t_prop *map_prop)
{
	map_prop->ordinate = 0;
	map_prop->abscissa = 0;
}

int	main(int argc, char **argv)
{
	t_prop	map_prop;
	t_point	**map;

	// void	*mlx_ptr;
	// void	*win_ptr;
	if (argc != 2)
		exit_message(EXIT_FAILURE, "Wrong number of arguments.\n");
	init_map_prop(&map_prop);
	map = load_map(argv[1], &map_prop);
	put_map(map, &map_prop);
	free_map(map, map_prop.ordinate);
	// mlx_ptr = mlx_init();
	// if (mlx_ptr == NULL)
	// {
	// 	free_map(map, ordinate);
	// 	exit_message("Failed to set up connection.\n");
	// }
	// ft_printf("Did set up connection.\n");
	// win_ptr = mlx_new_window(mlx_ptr, 1000, 500, "Test window");
	// mlx_key_hook(win_ptr, &print_key, NULL);
	// mlx_mouse_hook(win_ptr, &print_mouse, NULL);
	// mlx_expose_hook(win_ptr, &print_expose, NULL);
	// mlx_loop_hook(win_ptr, &loop_hook, NULL);
	// mlx_loop(mlx_ptr);
	// free_map(map, ordinate);
	// // free(win_ptr);
	// free(mlx_ptr);
	return (EXIT_SUCCESS);
}
