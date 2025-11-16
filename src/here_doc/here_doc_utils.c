/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:23:27 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/12 16:12:47 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_data_argv(t_data *data)
{
	int	i;

	i = 0;
	while (data->argv[i])
	{
		free(data->argv[i]);
		data->argv[i] = NULL;
		i++;
	}
	free(data->argv);
	data->argv = NULL;
}

void	alloc_without_limiter(t_data *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (data->argv[i])
	{
		if (ft_strncmp(data->argv[i], "<<", 3) == 0 && data->argv[i + 1])
		{
			i += 2;
			continue ;
		}
		count++;
		i++;
	}
	if (pipe_after_limiter(data))
		count += 1;
	data->here_doc_argv = malloc(sizeof(char *) * (count + 1));
	if (!data->here_doc_argv)
	{
		perror("malloc");
		exit(1);
	}
}

void	tab_without_limiter(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (pipe_after_limiter(data))
	{
		data->here_doc_argv[0] = ft_strdup("cat");
		j = 1;
	}
	while (data->argv[i])
	{
		if (ft_strncmp(data->argv[i], "<<", 3) == 0 && data->argv[i + 1])
		{
			i += 2;
			continue ;
		}
		data->here_doc_argv[j++] = ft_strdup(data->argv[i]);
		i++;
	}
	data->here_doc_argv[j] = NULL;
	update_argv_here_doc(data);
}

void	cpy_here_doc_argv(t_data *data)
{
	int	i;

	i = 0;
	if (!data->argv)
		return ;
	free_data_argv(data);
	i = 0;
	while (data->here_doc_argv[i] && data->here_doc_argv)
		i++;
	data->argv = malloc(sizeof(char *) * (i + 1));
	if (!data->argv)
		return ;
	i = 0;
	while (data->here_doc_argv[i])
	{
		data->argv[i] = ft_strdup(data->here_doc_argv[i]);
		if (!data->argv[i])
		{
			free_data_argv(data);
			return ;
		}
		i++;
	}
	data->argv[i] = NULL;
}
