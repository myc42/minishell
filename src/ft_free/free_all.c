/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 01:19:56 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/25 03:33:19 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	free_tab3(char ***tab3)
{
	int	i;

	if (!tab3)
		return ;
	i = 0;
	while (tab3[i])
	{
		free_tab(tab3[i]);
		tab3[i] = NULL;
		i++;
	}
	free(tab3);
}
void	free_all(t_data *data)
{
	if (!data)
		return ;
	if (data->input_clean)
	{
		free(data->input_clean);
		data->input_clean = NULL;
	}
	if (data->limiter)
	{
		free(data->limiter);
		data->limiter = NULL;
	}
	if (data->argv)
	{
		free_tab(data->argv);
		data->argv = NULL;
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
}
