/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:57:02 by dnovak            #+#    #+#             */
/*   Updated: 2024/10/24 10:56:33 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# ifndef ESCAPE_KEY
#  define ESCAPE_KEY 65307
# endif
# ifndef RED
#  define RED 65536
# endif
# ifndef GREEN
#  define GREEN 256
# endif
# ifndef BLUE
#  define BLUE 1
# endif

# include "libft/libft.h"
# include <fcntl.h>  // open
# include <math.h>   // math library
# include <mlx.h>    // MiniLibX
# include <stdlib.h> // exit

typedef struct s_point
{
	int			alt;
	double_t	x;
	double_t	y;
}				t_point;

typedef struct s_prop
{
	int			abscissa;
	int			ordinate;
}				t_prop;

// Utils
double_t		ft_double_max(double_t a, double_t b);
double_t		ft_double_min(double_t a, double_t b);

#endif // FDF_H
