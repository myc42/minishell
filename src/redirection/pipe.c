/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:13:39 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/14 21:13:57 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	do_pipe(int fd, int pipe_fd[2], pid_t pid)
{
	pipe(pipe_fd);
	if (pid == 0)
	{
		dup2(fd, 0);
		close(pipe_fd[0]);
	}
	else
	{
		wait(NULL);
		close(pipe_fd[1]);
		fd = pipe_fd[0];
	}
	return (fd);
}

int	count_pipeline(t_data *data)
{
	int	i;
	int	pipe_count;

	pipe_count = 0;
	i = 0;
	while (data->argv_only_cmd[i])
	{
		if (ft_strcmp(data->argv_only_cmd[i], "|") == 0)
		{
			pipe_count++;
		}
		i++;
	}
	return (pipe_count);
}
