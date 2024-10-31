/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:38:41 by dnovak            #+#    #+#             */
/*   Updated: 2024/10/30 23:43:48 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	open_file(char *file_name)
{
	int	len;
	int	fd;

	len = ft_strlen(file_name);
	if (len < 5)
		exit_message(EXIT_FAILURE, "Run program in format: ./fdf *.fdf\n");
	if (ft_strncmp((file_name + len - 4), ".fdf\0", 5) != 0)
		exit_message(EXIT_FAILURE, "Input *.fdf file.\n");
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		exit_message(EXIT_FAILURE, "Could not open the file.\n");
	return (fd);
}

static char	*load_first_line(int fd)
{
	char	*line;
	char	*trim;

	line = get_next_line(fd);
	if (line == NULL)
	{
		close(fd);
		exit_message(EXIT_FAILURE, "File is empty.\n");
	}
	trim = ft_strtrim(line, "\t\n\v\f\r ");
	free(line);
	if (trim == NULL)
	{
		free_file_descriptor(fd);
		exit_message(EXIT_FAILURE, "Could not allocate memory.\n");
	}
	return (trim);
}

static void	check_split(char **split, t_map *map, int fd)
{
	int	abscissa;
	int	a;

	abscissa = ft_split_len(split);
	if (map->prop.ordinate == 0)
		map->prop.abscissa = abscissa;
	else if (abscissa != map->prop.abscissa)
	{
		free_all(map, split, fd);
		exit_message(EXIT_FAILURE, "Wrong number of columns.\n");
	}
	a = 0;
	while (a < map->prop.abscissa)
	{
		if (!ft_isdigit(*split[a]) && (*split[a] != '-'
				|| !ft_isdigit(*(split[a] + 1))))
		{
			free_all(map, split, fd);
			exit_message(EXIT_FAILURE, "Wrong format of a map.\n");
		}
		a++;
	}
}

static char	*load_next_line(int fd, t_map *map)
{
	char	*line;
	char	*trim;

	line = get_next_line(fd);
	if (line == NULL)
		return (NULL);
	trim = ft_strtrim(line, "\t\n\v\f\r ");
	free(line);
	if (trim == NULL)
	{
		free_all(map, NULL, fd);
		exit_message(EXIT_FAILURE, "Could not allocate memory.\n");
	}
	return (trim);
}

void	load_map(char *file_name, t_map *map)
{
	int		fd;
	char	*line;
	char	**split;

	fd = open_file(file_name);
	line = load_first_line(fd);
	while (line != NULL)
	{
		split = ft_split(line, ' ');
		free(line);
		if (split == NULL)
		{
			free_all(map, split, fd);
			exit_message(EXIT_FAILURE, "Could not allocate memory.\n");
		}
		check_split(split, map, fd);
		expand_map(map, split, fd);
		map->prop.ordinate++;
		line = load_next_line(fd, map);
	}
	close(fd);
}
