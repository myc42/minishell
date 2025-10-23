/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:53:18 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/23 22:51:47 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_and_waitpid(t_data *data, pid_t pid)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	setup_signals();
	update_status_from_signal(status, data);
}

void	exe_pid_zero_one(int prev_pipe_read_fd, int i, t_data *data,
		int pipeline_nb, int *fds)
{
	reset_signals_child();
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
}

void	exe_pid_parent(int *prev_pipe_read_fd, int pipeline_nb, int *fds,
		int *i)
{
	if (*prev_pipe_read_fd != -1)
		close(*prev_pipe_read_fd);
	if (*i < pipeline_nb - 1)
	{
		*prev_pipe_read_fd = fds[0];
		close(fds[1]);
	}
	else
	{
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
}
