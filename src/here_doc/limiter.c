/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limiter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 02:33:44 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/26 15:23:37 by macoulib         ###   ########.fr       */
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

void	find_all_limiters(t_data *data)
{
	int	count;
	int	i;
	int	j;

	i = 0;
	j = 0;
	count = check_nbr_limiter(data);
	data->limiter = (char **)malloc(sizeof(char *) * (count + 1));
	if (!data->limiter)
		return ;
	while (data->argv[i])
	{
		if (ft_strncmp(data->argv[i], "<<", 3) == 0 && data->argv[i + 1])
		{
			data->limiter[j] = ft_strdup(data->argv[i + 1]);
			if (!data->limiter[j])
				return ;
			j++;
		}
		i++;
	}
	data->limiter[j] = NULL;
}
