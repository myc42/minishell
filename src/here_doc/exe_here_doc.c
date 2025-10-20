/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:50:49 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/20 03:07:02 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exe_here_docx(t_data *data)
{
	int		i;
	int		pipeline_nb;
	int		prev_pipe_read_fd;
	int		fds[2];
	pid_t	pid;
	int		status;

	i = 0;
	create_pipeline_tab(data);
	pipeline_nb = count_pipeline(data) + 1;
	while (i < pipeline_nb)
	{
		if (i < pipeline_nb - 1)
		{
			if (pipe(fds) == -1)
			{
				perror("pipe");
				return ;
			}
		}
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
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
			//exe_cmd(data, &i, env);
			exit(EXIT_FAILURE);
		}
		else
		{
			if (prev_pipe_read_fd != -1)
				close(prev_pipe_read_fd);
			if (i < pipeline_nb - 1)
			{
				prev_pipe_read_fd = fds[0];
				close(fds[1]);
			}
			else
			{
				prev_pipe_read_fd = -1;
			}
			i++;
		}
		if (data->infile_fd != -1)
			close(data->infile_fd);
		if (data->outfile_fd != -1)
			close(data->outfile_fd);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid, &status, 0);
		setup_signals();
		update_status_from_signal(status, data);
	}
}
