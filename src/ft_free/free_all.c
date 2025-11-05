/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:43:14 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/05 19:46:14 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
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

void	free_fd_array(int **fds)
{
	int	i;

	if (!fds)
		return ;
	i = 0;
	while (fds[i])
	{
		free(fds[i]);
		fds[i] = NULL;
		i++;
	}
	free(fds);
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
		free_tab(data->limiter);
		data->limiter = NULL;
	}
	if (data->argv)
	{
		free_tab(data->argv);
		data->argv = NULL;
	}
	free_utils2(data);
	free_utils3(data);
}
