/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:27:57 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/16 17:53:49 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_count_cmds_pipeline(t_data *data)
{
	int	count;

	count = 0;
	if (!data || !data->argv_pipeline)
		return (0);
	while (data->argv_pipeline[count] != NULL)
		count++;
	return (count);
}

void	free_pipeline_fd_two(t_data *data, int i)
{
	i = 0;
	while (data->pipeline_out_fds[i])
	{
		if (*(data->pipeline_out_fds[i]) != STDOUT_FILENO)
			close(*(data->pipeline_out_fds[i]));
		free(data->pipeline_out_fds[i]);
		i++;
	}
	free(data->pipeline_out_fds);
	data->pipeline_out_fds = NULL;
}

void	free_pipeline_fds(t_data *data)
{
	int	i;

	if (!data)
		return ;
	if (data->pipeline_in_fds)
	{
		i = 0;
		while (data->pipeline_in_fds[i])
		{
			if (data->pipeline_in_fds[i]
				&& *(data->pipeline_in_fds[i]) != STDIN_FILENO)
				close(*(data->pipeline_in_fds[i]));
			free(data->pipeline_in_fds[i]);
			i++;
		}
		free(data->pipeline_in_fds);
		data->pipeline_in_fds = NULL;
	}
	if (data->pipeline_out_fds)
	{
		free_pipeline_fd_two(data, i);
	}
}

void	free_argv_pipeline(t_data *data)
{
	int	i;
	int	j;

	if (!data || !data->argv_pipeline)
		return ;
	i = 0;
	while (data->argv_pipeline[i])
	{
		j = 0;
		while (data->argv_pipeline[i][j])
		{
			free(data->argv_pipeline[i][j]);
			j++;
		}
		free(data->argv_pipeline[i]);
		i++;
	}
	free(data->argv_pipeline);
	data->argv_pipeline = NULL;
}

int	exe_echox(t_data *data)
{
	cpy_clean_quotes_to_av(data);
	ft_split_by_pipe(data);
	setup_redirections(data);
	execute_pipeline(data);
	free_pipeline_fds(data);
	free_argv_pipeline(data);
	return (0);
}
