/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:50:49 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/22 21:09:33 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	if_pid_zero_one(int prev_pipe_read_fd, int i, int outfile)
{
	reset_signals_child();
	if (prev_pipe_read_fd != -1)
	{
		dup2(prev_pipe_read_fd, 0);
		close(prev_pipe_read_fd);
	}
	else if (i == 0)
	{
		dup2(outfile, 0);
		close(outfile);
	}
}

void	if_pid_zero_two(t_data *data, int i, int pipeline_nb, int *fds)
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

void	pid_parent_zero(int *prev_pipe_read_fd, int pipeline_nb, int *i,
		int *fds)
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

void	ft_forkpid(pid_t *pid)
{
	*pid = fork();
	if (*pid == -1)
		return ;
}

void	exe_heredoc(t_data *data, int outfile)
{
	int	prev_pipe_read_fd;

	prev_pipe_read_fd = -1;
	if (data->argv_pipeline[0] != NULL && data->argv_pipeline != NULL)
		execute_pipeline(data, outfile);
	free_pipeline_fds(data);
	free_argv_pipeline(data);
	free_fds_and_pipelines(data);
	free_all(data);
	end_exe_heredoc(data, outfile, &prev_pipe_read_fd);
}
