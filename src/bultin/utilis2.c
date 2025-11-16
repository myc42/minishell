/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 02:40:28 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/16 02:52:00 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	bult_echo(t_data *data)
{
	int	i;

	i = 0;
	while (data->argv[i])
		i++;
	if (i < 3)
		return (builtin_echo(data->argv, data));
	else
		return (exe_echox(data));
}

void	free_data_pin(t_data *data)
{
	int	i;

	i = 0;
	while (data->pipeline_in_fds[i])
	{
		if (data->pipeline_in_fds[i][0] > 0)
			close(data->pipeline_in_fds[i][0]);
		if (data->pipeline_in_fds[i][1] > 0)
			close(data->pipeline_in_fds[i][1]);
		free(data->pipeline_in_fds[i]);
		i++;
	}
	free(data->pipeline_in_fds);
	data->pipeline_in_fds = NULL;
}

void	free_data_pout(t_data *data)
{
	int	i;

	i = 0;
	while (data->pipeline_out_fds[i])
	{
		if (data->pipeline_out_fds[i][0] > 0)
			close(data->pipeline_out_fds[i][0]);
		if (data->pipeline_out_fds[i][1] > 0)
			close(data->pipeline_out_fds[i][1]);
		free(data->pipeline_out_fds[i]);
		i++;
	}
	free(data->pipeline_out_fds);
	data->pipeline_out_fds = NULL;
}

void	free_data_erro(t_data *data)
{
	int	i;

	i = 0;
	while (data->pipeline_err_fds[i])
	{
		if (data->pipeline_err_fds[i][0] > 0)
			close(data->pipeline_err_fds[i][0]);
		if (data->pipeline_err_fds[i][1] > 0)
			close(data->pipeline_err_fds[i][1]);
		free(data->pipeline_err_fds[i]);
		i++;
	}
	free(data->pipeline_err_fds);
	data->pipeline_err_fds = NULL;
}

void	free_data_echo(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->echo_pipline[i])
	{
		j = 0;
		while (data->echo_pipline[i][j])
		{
			free(data->echo_pipline[i][j]);
			j++;
		}
		free(data->echo_pipline[i]);
		i++;
	}
	free(data->echo_pipline);
	data->echo_pipline = NULL;
}

void	free_fds_and_pipelines(t_data *data)
{
	if (data->infile_fd > 0)
		close(data->infile_fd);
	if (data->outfile_fd > 0)
		close(data->outfile_fd);
	if (data->error_fd > 0)
		close(data->error_fd);
	if (data->pipeline_in_fds)
		free_data_pin(data);
	if (data->pipeline_out_fds)
		free_fds_and_pipelines(data);
	if (data->pipeline_err_fds)
		free_data_erro(data);
	if (data->echo_pipline)
		free_data_echo(data);
}
