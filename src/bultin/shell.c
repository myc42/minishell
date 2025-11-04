/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 19:27:13 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/04 19:27:13 by macoulib         ###   ########.fr       */
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
	data->argv_clean_quotes = NULL;
	data->argv_only_cmd = NULL;
	data->here_doc_argv = NULL;
	data->argv_pipeline = NULL;
	data->echo_pipline = NULL;
	data->limiter = NULL;
	data->pipeline_in_fds = NULL;
	data->pipeline_out_fds = NULL;
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
	if (!data->envp)
	{
		ft_putstr_fd("Error: env copy failed\n", 2);
		exit(1);
	}
	setup_signals();
}

void	start_data(t_data *data)
{
	if (!data)
		return ;
	data->input_clean = NULL;
	data->argv = NULL;
	data->argv_clean_quotes = NULL;
	data->argv_only_cmd = NULL;
	data->here_doc_argv = NULL;
	data->argv_pipeline = NULL;
	data->echo_pipline = NULL;
	data->limiter = NULL;
	data->pipeline_in_fds = NULL;
	data->pipeline_out_fds = NULL;
	data->infile_fd = -1;
	data->outfile_fd = -1;
	data->error_fd = -1;
}
