/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:53:50 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/16 21:15:32 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_var_exe(int *i, int *prev_pipe_read_fd, t_data *data, char *input)
{
	*i = 0;
	*prev_pipe_read_fd = -1;
	first_argv_in_tab(data, input, data->envp);
}

int	update_cmd_pipenbr(t_data *data, int *pipeline_nb)
{
	if (!redirect_and_cmds(data, 0))
	{
		*pipeline_nb = 0;
		return (0);
	}
	else
		*pipeline_nb = count_pipeline(data) + 1;
	return (1);
}

void	signal_and_waitpid(t_data *data, pid_t pid)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		status = 1;
		setup_signals();
		return ;
	}
	setup_signals();
	update_status_from_signal(status, data);
}
