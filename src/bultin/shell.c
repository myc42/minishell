/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/10/14 17:38:31 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/14 17:38:31 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	init_shell(t_data *data)
{
	if (!data)
		return ;
	data->envp = NULL;
	data->input_clean = NULL;
	data->argv = NULL;
	data->argv_only_cmd = NULL;
	data->here_doc_argv = NULL;
	data->argv_pipeline = NULL;
	data->limiter = NULL;
	data->infile_fd = -1;
	data->outfile_fd = -1;
	data->error_fd = -1;
	data->last_status = 0;
	data->len_env = 0;
}

void	init_data(t_data *data, char **envp)
{
	init_shell(data);
	data->envp = copy_envp(envp);
	data->last_status = 0;
	if (!data->envp)
	{
		ft_putstr_fd("Error: env copy failed\n", 2);
		exit(1);
	}
	setup_signals();
}
