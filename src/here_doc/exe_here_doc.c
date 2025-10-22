/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:50:49 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/22 03:33:12 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	if_pid_zero_one(int prev_pipe_read_fd, int i, int outfile)
{
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
	pid_t	pid;
	int		pipeline_nb;
	int		prev_pipe_read_fd;
	int		fds[2];
	int		i;

	init_var_heredoc(data, &prev_pipe_read_fd, &pipeline_nb, &i);
	while (i < pipeline_nb)
	{
		if (i < pipeline_nb - 1)
			pipe_fd(fds);
		ft_forkpid(&pid);
		if (pid == 0)
		{
			reset_signals_child();
			signal_and_waitpid(data, pid);
			if_pid_zero_one(prev_pipe_read_fd, i, outfile);
			if_pid_zero_two(data, i, pipeline_nb, fds);
			exe_cmd(data, &i, data->envp);
			exit(EXIT_FAILURE);
		}
		else
		{
			pid_parent_zero(&prev_pipe_read_fd, pipeline_nb, &i, fds);
			signal_and_waitpid(data, pid);
		}
		
	}
	unlink(".test");
	unlink(".test2");
}
