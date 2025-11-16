/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:23:42 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/14 21:14:29 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	alloc_for_onlycmd(t_data *data)
{
	int	nbr_cmd;

	nbr_cmd = count_cmd_elements(data);
	data->argv_only_cmd = malloc(sizeof(char *) * (nbr_cmd + 1));
	if (!data->argv_only_cmd)
		return ;
}

int	cpy_to_argv_onlycmd(t_data *data, int *i, int *j)
{
	data->argv_only_cmd[*j] = ft_strdup(data->argv[*i]);
	if (!data->argv_only_cmd[*j])
	{
		return (0);
	}
	(*j)++;
	(*i)++;
	return (1);
}

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
			if (data->argv[i + 1])
				i += 2;
			else
				i += 1;
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
	alloc_for_onlycmd(data);
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
			if (!cpy_to_argv_onlycmd(data, &i, &j))
				return (free_tab(data->argv_only_cmd), 0);
		}
	}
	data->argv_only_cmd[j] = NULL;
	return (1);
}

int	check_double_pipe(t_data *data)
{
	int	i;

	i = 0;
	while (data->argv[i] && data->argv[i + 1])
	{
		if (ft_strcmp(data->argv[i], "|") == 0 && ft_strcmp(data->argv[i + 1],
				"|") == 0)
		{
			printf("syntax error near unexpected token `|'\n");
			return (1);
		}
		i++;
	}
	return (0);
}
