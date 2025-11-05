/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_principal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 20:43:21 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/05 19:49:05 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	management_status(t_data *data, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		data->last_status = 128 + WTERMSIG(status);
	else
		data->last_status = WEXITSTATUS(status);
}

void	unlink_free(t_data *data)
{
	unlink(".test");
	unlink(".test2");
	free_all(data);
}

void	call_signal(void)
{
	reset_signals_child();
	signal(SIGINT, handle_sigint_heredoc);
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
			call_signal();
			if_pid_zero_one(prev_pipe_read_fd, i, outfile);
			if_pid_zero_two(data, i, pipeline_nb, fds);
			exe_cmd(data, &i, data->envp);
			exit(EXIT_FAILURE);
		}
		else
		{
			pid_parent_zero(&prev_pipe_read_fd, pipeline_nb, &i, fds);
			management_status(data, pid);
		}
	}
	unlink_free(data);
}

