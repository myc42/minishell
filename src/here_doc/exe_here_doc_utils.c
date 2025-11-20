/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_here_doc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:29:02 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/20 18:15:04 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_waitpid(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
}

void	pipe_fd(int *fds)
{
	if (pipe(fds) == -1)
	{
		perror("pipe");
		return ;
	}
}

void	init_var_heredoc(t_data *data, int *prev_pipe_read_fd, int *pipeline_nb,
		int *i)
{
	*i = 0;
	*prev_pipe_read_fd = -1;
	*pipeline_nb = count_pipeline(data) + 1;
}

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	exit(130);
}

void	end_exe_heredoc(t_data *data, int fd, int *prev)
{
	if (fd > 1)
		close(fd);
	if (*prev > 1)
		close(*prev);
	free_fds_and_pipelines(data);
	unlink(".test");
	unlink(".test2");
	free_all(data);
}
