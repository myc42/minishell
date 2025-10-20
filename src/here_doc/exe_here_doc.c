/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:50:49 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/20 04:22:57 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exe_heredoc(t_data *data, int outfile)
{
	pid_t	pid;
	int		pipeline_nb;
	int		prev_pipe_read_fd;
	int		fds[2];
	int		i;
	int		status;

	i = 0;
	prev_pipe_read_fd = -1;
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
			exe_cmd(data, &i, data->envp);
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
		waitpid(pid, &status, 0);
	}
	unlink("outfilex.txt");
}