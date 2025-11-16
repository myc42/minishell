/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:33:40 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/14 21:13:35 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_args_in_cmd(t_data *data, int start_index)
{
	int	count;
	int	i;

	count = 0;
	i = start_index;
	while (data->argv_only_cmd[i] && ft_strcmp(data->argv_only_cmd[i],
			"|") != 0)
	{
		count++;
		i++;
	}
	return (count);
}

int	alloc_argv_pipeline(t_data *data, int j, int num_args)
{
	data->argv_pipeline[j] = (char **)malloc((num_args + 1) * sizeof(char *));
	if (data->argv_pipeline[j] == NULL)
		return (0);
	return (1);
}

int	alloc_taboftab_pipeline(t_data *data)
{
	int	num_cmds;

	num_cmds = count_pipeline(data) + 1;
	data->argv_pipeline = (char ***)malloc((num_cmds + 1) * sizeof(char **));
	if (data->argv_pipeline == NULL)
		return (0);
	return (1);
}

static int	copy_cmd_args(t_data *data, int *i, int j, int num_args)
{
	int	k;

	k = 0;
	while (k < num_args)
	{
		data->argv_pipeline[j][k] = ft_strdup(data->argv_only_cmd[*i]);
		if (!data->argv_pipeline[j][k])
		{
			free_tab3(data->argv_pipeline);
			return (0);
		}
		(*i)++;
		k++;
	}
	data->argv_pipeline[j][k] = NULL;
	if (data->argv_only_cmd[*i] && ft_strcmp(data->argv_only_cmd[*i], "|") == 0)
		(*i)++;
	return (1);
}

void	create_pipeline_tab(t_data *data)
{
	int	i;
	int	j;
	int	num_args;

	i = 0;
	j = 0;
	if (!alloc_taboftab_pipeline(data))
		return ;
	while (data->argv_only_cmd[i])
	{
		num_args = count_args_in_cmd(data, i);
		if (!alloc_argv_pipeline(data, j, num_args))
			return ;
		if (!copy_cmd_args(data, &i, j, num_args))
			return ;
		j++;
	}
	data->argv_pipeline[j] = NULL;
}
