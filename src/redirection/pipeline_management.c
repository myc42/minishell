/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:24:59 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/05 18:25:00 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../includes/minishell.h"

int	count_pipeline(t_data *data)
{
	int	i;
	int	pipe_count;

	pipe_count = 0;
	i = 0;
	while (data->argv_only_cmd[i])
	{
		if (strcmp(data->argv_only_cmd[i], "|") == 0)
		{
			pipe_count++;
		}
		i++;
	}
	return (pipe_count);
}

int	count_args_in_cmd(t_data *data, int start_index)
{
	int	count;
	int	i;

	count = 0;
	i = start_index;
	while (data->argv_only_cmd[i] && strcmp(data->argv_only_cmd[i], "|") != 0)
	{
		count++;
		i++;
	}
	return (count);
}

void	alloc_argv_pipeline(t_data *data, int j, int num_args)
{
	data->argv_pipeline[j] = (char **)malloc((num_args + 1) * sizeof(char *));
	if (data->argv_pipeline[j] == NULL)
		return ;
}

void	alloc_taboftab_pipeline(t_data *data)
{
	int	num_cmds;

	num_cmds = count_pipeline(data) + 1;
	data->argv_pipeline = (char ***)malloc((num_cmds + 1) * sizeof(char **));
	if (data->argv_pipeline == NULL)
		return ;
}
void	create_pipeline_tab(t_data *data)
{
	int	i;
	int	j;
	int	k;
	int	num_args;

	i = 0;
	j = 0;
	alloc_taboftab_pipeline(data);
	while (data->argv_only_cmd[i])
	{
		num_args = count_args_in_cmd(data, i);
		alloc_argv_pipeline(data, j, num_args);
		k = 0;
		while (k < num_args)
		{
			data->argv_pipeline[j][k] = ft_strdup(data->argv_only_cmd[i]);
			i++;
			k++;
		}
		data->argv_pipeline[j][k] = NULL;
		if (data->argv_only_cmd[i] && strcmp(data->argv_only_cmd[i], "|") == 0)
			i++;
		j++;
	}
	data->argv_pipeline[j] = NULL;
}
