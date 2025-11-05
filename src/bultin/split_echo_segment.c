/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_echo_segment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:32:15 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/05 19:32:33 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_count_pipes(char **args)
{
	int	i;
	int	count;

	count = 1;
	if (!args || !args[0])
		return (0);
	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "|") == 0)
			count++;
		i++;
	}
	return (count);
}

char	**ft_copy_segment(char **start, char **end)
{
	char	**segment;
	int		len;
	int		i;

	if (!start || !end)
		return (NULL);
	len = end - start;
	if (len <= 0)
		return (NULL);
	segment = malloc(sizeof(char *) * (len + 1));
	if (!segment)
		return (NULL);
	i = 0;
	while (start < end)
	{
		segment[i] = strdup(*start);
		start++;
		i++;
	}
	segment[i] = NULL;
	return (segment);
}

int	init_var_split(t_data *data, int *i, int *count, int *cmd_index)
{
	*count = ft_count_pipes(data->argv);
	data->argv_pipeline = malloc(sizeof(char **) * (*count + 1));
	if (!data->argv_pipeline)
		return (0);
	*cmd_index = 0;
	*i = 0;
	return (1);
}

void	ft_split_by_pipe(t_data *data)
{
	int		i;
	int		count;
	int		cmd_index;
	char	**segment_start;

	if (!init_var_split(data, &i, &count, &cmd_index))
		return ;
	if (!data || !data->argv)
		return ;
	segment_start = data->argv;
	while (data->argv[i])
	{
		if (ft_strcmp(data->argv[i], "|") == 0)
		{
			data->argv_pipeline[cmd_index] = ft_copy_segment(segment_start,
					&data->argv[i]);
			segment_start = &data->argv[i + 1];
			cmd_index++;
		}
		i++;
	}
	data->argv_pipeline[cmd_index] = ft_copy_segment(segment_start,
			&data->argv[i]);
	data->argv_pipeline[cmd_index + 1] = NULL;
}
