/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 01:19:56 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/22 01:28:53 by macoulib         ###   ########.fr       */
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

	i = 0;
	if (!tab3)
		return ;
	while (tab3[i])
	{
		free_tab(tab3[i]);
		i++;
	}
	free(tab3);
}

void	free_all(t_data *data)
{
	if (!data)
		return ;
	free(data->input_clean);
	data->input_clean = NULL;
	free(data->limiter);
	data->limiter = NULL;
	free_tab(data->argv);
	data->argv = NULL;
	free_tab(data->argv_only_cmd);
	data->argv_only_cmd = NULL;
	free_tab(data->here_doc_argv);
	data->here_doc_argv = NULL;
	free_tab3(data->argv_pipeline);
	data->argv_pipeline = NULL;
	free_tab(data->envp);
	data->envp = NULL;
}

