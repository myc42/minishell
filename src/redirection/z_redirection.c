/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_redirection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:24:49 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/05 18:24:50 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

int	fd_and_cmd_tab(t_data *data)
{
	data->infile_fd = -1;
	data->outfile_fd = -1;
	data->error_fd = -1;
	data->pipeline_in_fds = NULL;
	data->pipeline_out_fds = NULL;
	if (!redirect_and_cmds(data))
		return (0);
	return (1);
}
