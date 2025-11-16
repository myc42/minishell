/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_redirection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:46:46 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/16 21:10:06 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	fd_and_cmd_tab(t_data *data)
{
	data->infile_fd = -1;
	data->outfile_fd = -1;
	data->error_fd = -1;
	if (!redirect_and_cmds(data, 0))
		return (0);
	return (1);
}
