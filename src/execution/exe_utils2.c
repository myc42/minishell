/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:38:55 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/05 19:39:09 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_var_exe(int *i, int *prev_pipe_read_fd, t_data *data, char *input,
		char **env)
{
	*i = 0;
	*prev_pipe_read_fd = -1;
	first_argv_in_tab(data, input, env);
}

int	update_cmd_pipenbr(t_data *data, int *pipeline_nb)
{
	if (!redirect_and_cmds(data))
		return (0);
	*pipeline_nb = count_pipeline(data) + 1;
	return (1);
}
