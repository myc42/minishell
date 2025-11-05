/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 22:51:13 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/05 19:48:22 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

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
		perror("minishell: fork");
}
