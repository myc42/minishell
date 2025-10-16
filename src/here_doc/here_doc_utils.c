/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:23:27 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/16 22:47:06 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	alloc_without_limiter(t_data *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (data->argv[i])
	{
		if (ft_strncmp(data->argv[i], "<<", 3) == 0 && data->argv[i + 1])
		{
			i += 2;
			continue ;
		}
		count++;
		i++;
	}
	data->argv_only_cmd = malloc(sizeof(char *) * (count + 1));
	if (!data->argv_only_cmd)
	{
		perror("malloc");
		exit(1);
	}
}

void	tab_without_limiter(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->argv[i])
	{
		if (ft_strncmp(data->argv[i], "<<", 3) == 0 && data->argv[i + 1])
		{
			i += 2;
			continue ;
		}
		data->argv_only_cmd[j++] = ft_strdup(data->argv[i]);
		i++;
	}
	data->argv_only_cmd[j] = NULL;
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


