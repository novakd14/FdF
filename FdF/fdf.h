/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:57:02 by dnovak            #+#    #+#             */
/*   Updated: 2024/10/30 23:24:36 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# ifndef X_SIZE
#  define X_SIZE 1000
# endif
# ifndef Y_SIZE
#  define Y_SIZE 500
# endif

# ifndef ESCAPE_KEY
#  define ESCAPE_KEY 0XFF1B
# endif
# ifndef RED
#  define RED 0x010000
# endif
# ifndef GREEN
#  define GREEN 0x000100
# endif
# ifndef BLUE
#  define BLUE 0x000001
# endif
# ifndef WHITE
#  define WHITE 0xFFFFFF
# endif

# include "libft/libft.h"
# include <fcntl.h>  // open
# include <math.h>   // math library
# include <mlx.h>    // MiniLibX
# include <stdlib.h> // exit

typedef struct s_point
{
	int			alt;
	int			color;
	double_t	x;
	double_t	y;
	double_t	x_orig;
	double_t	y_orig;
}				t_point;

typedef struct s_map_prop
{
	int			abscissa;
	int			ordinate;
	double_t	x_min;
	double_t	x_max;
	double_t	x_size;
	double_t	y_min;
	double_t	y_max;
	double_t	y_size;
}				t_map_prop;

typedef struct s_map
{
	t_point		**points;
	t_map_prop	prop;
}				t_map;

typedef struct s_img_prop
{
	int			bpp;
	int			size_line;
	int			endian;
	double_t	x_offset;
	double_t	y_offset;
	double_t	scale;
}				t_img_prop;

typedef struct s_display
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	int			x_size;
	int			y_size;
	t_img_prop	img_prop;
	char		*data;
}				t_display;

typedef struct s_fdf
{
	t_map		*map;
	t_display	*disp;
}				t_fdf;

// Loading map from file
void			load_map(char *file_name, t_map *map);
void			expand_map(t_map *map, char **split, int fd);

// Projection
void			setup_projection(t_map *map);
void			set_scale(t_map *map, t_display *disp);
void			scale_projection(t_map *map, t_display *disp);

// Put map to image
void			ft_put_map_to_image(t_map *map, t_display *disp);

// Setup functions
void			setup_display(t_display *disp, t_map *map);
void			setup_events(t_fdf *fdf);

// Cleaning functions
void			free_map(t_map *map);
void			free_split_array(char **array);
void			free_file_descriptor(int fd);
void			free_all(t_map *map, char **split, int fd);
void			end_session(t_display *disp);

// Utils
int				ft_split_len(char **array);
void			exit_message(int result, char *message);
double_t		ft_double_max(double_t a, double_t b);
double_t		ft_double_min(double_t a, double_t b);

#endif // FDF_H
