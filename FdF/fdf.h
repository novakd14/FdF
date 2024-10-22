/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:57:02 by dnovak            #+#    #+#             */
/*   Updated: 2024/10/22 11:18:35 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define ESCAPE_KEY 65307

# include "libft/libft.h"
# include <math.h>
# include <mlx.h>
# include <stdlib.h>

typedef struct s_point
{
	int	alt;
	int	x;
	int	y;
}		t_point;

#endif // FDF_H
