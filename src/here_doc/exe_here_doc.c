/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:50:49 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/24 18:24:06 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	end_exe_heredoc(data, outfile, &prev_pipe_read_fd);
}
