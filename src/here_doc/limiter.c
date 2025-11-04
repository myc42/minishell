/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limiter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 23:09:34 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/04 23:31:55 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_nbr_limiter(t_data *data)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (data->argv[i])
	{
		if (ft_strncmp(data->argv[i], "<<", 3) == 0 && data->argv[i + 1])
			count++;
		i++;
	}
	return (count);
}

void	find_all_limiters(t_data *data)
{
	int	count;
	int	i;
	int	j;

	count = check_nbr_limiter(data);
	data->limiter = malloc(sizeof(char *) * (count + 1));
	if (!data->limiter)
		return ;

	i = 0;
	j = 0;
	while (data->argv[i])
	{
		if (ft_strncmp(data->argv[i], "<<", 3) == 0 && data->argv[i + 1])
		{
			data->limiter[j++] = ft_strdup(data->argv[i + 1]);
		}
		i++;
	}
	data->limiter[j] = NULL;
}

