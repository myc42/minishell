/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:44:23 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/05 19:47:02 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_utils3(t_data *data)
{
	if (data->pipeline_in_fds)
	{
		free_fd_array(data->pipeline_in_fds);
		data->pipeline_in_fds = NULL;
	}
	if (data->pipeline_out_fds)
	{
		free_fd_array(data->pipeline_out_fds);
		data->pipeline_out_fds = NULL;
	}
	if (data->infile_fd > 2)
	{
		close(data->infile_fd);
		data->infile_fd = -1;
	}
	if (data->outfile_fd > 2)
	{
		close(data->outfile_fd);
		data->outfile_fd = -1;
	}
	if (data->error_fd > 2)
	{
		close(data->error_fd);
		data->error_fd = -1;
	}
}

void	free_utils2(t_data *data)
{
	if (data->argv_clean_quotes)
	{
		free_tab(data->argv_clean_quotes);
		data->argv_clean_quotes = NULL;
	}
	if (data->argv_only_cmd)
	{
		free_tab(data->argv_only_cmd);
		data->argv_only_cmd = NULL;
	}
	if (data->here_doc_argv)
	{
		free_tab(data->here_doc_argv);
		data->here_doc_argv = NULL;
	}
	if (data->argv_pipeline)
	{
		free_tab3(data->argv_pipeline);
		data->argv_pipeline = NULL;
	}
	if (data->echo_pipline)
	{
		free_tab3(data->echo_pipline);
		data->echo_pipline = NULL;
	}
}
