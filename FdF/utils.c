/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:43:18 by dnovak            #+#    #+#             */
/*   Updated: 2024/10/29 20:07:26 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Returns length of array of strings, ended with NULL.
int	ft_split_len(char **array)
{
	int	len;

	if (array == NULL)
		return (-1);
	len = 0;
	while (array[len] != NULL)
		len++;
	return (len);
}

void	exit_message(int result, char *message)
{
	if (result == EXIT_FAILURE)
	{
		write(STDERR_FILENO, message, ft_strlen(message));
		exit(EXIT_FAILURE);
	}
	write(STDOUT_FILENO, message, ft_strlen(message));
	exit(EXIT_SUCCESS);
}

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
