/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:43:18 by dnovak            #+#    #+#             */
/*   Updated: 2024/10/22 12:50:04 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double_t	ft_double_max(double_t a, double_t b)
{
	if (a > b)
		return (a);
	return (b);
}

double_t	ft_double_min(double_t a, double_t b)
{
	if (a < b)
		return (a);
	return (b);
}
