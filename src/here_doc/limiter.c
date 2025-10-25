/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limiter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 02:33:44 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/25 03:33:52 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_nbr_limiter(t_data *data)
{
	int	i;
	int	limiter;

	limiter = 0;
	i = 0;
	while (data->argv[i])
	{
		if (ft_strncmp(data->argv[i], "<<", 3) == 0 && data->argv[i + 1])
			limiter++;
		i++;
	}
	if (limiter > 1)
		return (1);
	return (0);
}

int	find_limiter(t_data *data)
{
	int	i;

	i = 0;
	while (data->argv[i])
	{
		if (ft_strncmp(data->argv[i], "<<", 3) == 0 && data->argv[i + 1])
		{
			if (data->limiter)
				free(data->limiter);
			data->limiter = ft_strdup(data->argv[i + 1]);
		}
		i++;
	}
	return (data->limiter != NULL);
}

void	find_limiter_mult(t_data *data)
{
	int	i;
	int	found_count;

	i = 0;
	found_count = 0;
	while (data->argv[i])
		i++;
	i--;
	while ( i >= 0)
	{
		if (ft_strncmp(data->argv[i], "<<", 3) == 0 && data->argv[i + 1])
		{
			if (found_count == 0)
			{
				data->limiter = ft_strdup(data->argv[i + 1]);
				found_count++;
			}
			else if (found_count == 1)
			{
				data->limiter2 = ft_strdup(data->argv[i + 1]);
				found_count++;
				break ;
			}
		}
		i--;
	}
}
