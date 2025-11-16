/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:53:18 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/16 16:56:33 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_input_fd(int prev_pipe_read_fd, int i, t_data *data)
{
	if (prev_pipe_read_fd != -1)
	{
		dup2(prev_pipe_read_fd, 0);
		close(prev_pipe_read_fd);
	}
	else if (i == 0 && data->infile_fd != -1)
	{
		dup2(data->infile_fd, 0);
		close(data->infile_fd);
	}
}

void	set_output_fd(int i, int pipeline_nb, t_data *data, int *fds)
{
	if (i < pipeline_nb - 1)
	{
		close(fds[0]);
		dup2(fds[1], 1);
		close(fds[1]);
	}
	else if (data->outfile_fd != -1)
	{
		dup2(data->outfile_fd, 1);
		close(data->outfile_fd);
	}
	else if (data->error_fd != -1)
	{
		dup2(data->error_fd, 1);
		close(data->error_fd);
	}
}

void	exe_pid_parent(int *prev_pipe_read_fd, int pipeline_nb, int *fds,
		int *i)
{
	if (*i < pipeline_nb - 1)
	{
		close(fds[1]);
		if (*prev_pipe_read_fd != -1)
			close(*prev_pipe_read_fd);
		*prev_pipe_read_fd = fds[0];
	}
	else
	{
		if (*prev_pipe_read_fd != -1)
			close(*prev_pipe_read_fd);
		*prev_pipe_read_fd = -1;
	}
	(*i)++;
}

void	close_infile_outfile(t_data *data, pid_t pid)
{
	(void)pid;
	if (data->infile_fd != -1)
		close(data->infile_fd);
	if (data->outfile_fd != -1)
		close(data->outfile_fd);
	if (data->error_fd != -1)
		close(data->error_fd);
}
