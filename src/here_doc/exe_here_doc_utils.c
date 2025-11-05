/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_here_doc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 23:31:33 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/05 19:48:07 by macoulib         ###   ########.fr       */
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
