/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:23:42 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/11 18:53:45 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_cmd_elements(t_data *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (data->argv && data->argv[i])
	{
		if (is_redirection_operator(data->argv[i]))
		{
			i += 2;
		}
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

int	only_cmd_tab(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!data->argv || !data->argv[0])
		return (data->argv_only_cmd = NULL, 0);
	data->argv_only_cmd = malloc(sizeof(char *) * (count_cmd_elements(data)
				+ 1));
	if (!data->argv_only_cmd)
		return (0);
	while (data->argv[i])
	{
		if (is_redirection_operator(data->argv[i]))
		{
			if (data->argv[i + 1])
				i += 2;
			else
				i += 1;
		}
		else
		{
			data->argv_only_cmd[j] = ft_strdup(data->argv[i]);
			if (!data->argv_only_cmd[j])
				return (0);
			j++;
			i++;
		}
	}
	data->argv_only_cmd[j] = NULL;
	return (1);
}



