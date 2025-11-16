/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grep_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 14:51:20 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/14 20:52:01 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	search_grep(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (ft_strcmp(argv[i], "grep") == 0)
			return (1);
		i++;
	}
	return (0);
}

static int	search_grep_pipe(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (ft_strcmp(argv[i], "grep") == 0 && argv[i + 2] && ft_strcmp(argv[i
					+ 2], "|") == 0)
			return (1);
		i++;
	}
	return (0);
}

void	cpy_new_only_cmd(t_data *data, char **argv_cpy)
{
	int	k;
	int	i;

	k = 0;
	i = 0;
	free_tab(data->argv_only_cmd);
	data->argv_only_cmd = NULL;
	while (argv_cpy[k])
		k++;
	data->argv_only_cmd = malloc(sizeof(char *) * (k + 1));
	if (!data->argv_only_cmd)
	{
		free_tab(argv_cpy);
		return ;
	}
	while (i < k)
	{
		data->argv_only_cmd[i] = ft_strdup(argv_cpy[i]);
		i++;
	}
	data->argv_only_cmd[k] = NULL;
}

void	while_to_cpy(t_data *data, int *i, int *j, char **argv_cpy)
{
	while (data->argv_only_cmd[*i])
	{
		if (ft_strcmp(data->argv_only_cmd[*i], "grep") == 0
			&& search_grep_pipe(data->argv_only_cmd))
		{
			*i += 3;
			continue ;
		}
		argv_cpy[(*j)++] = ft_strdup(data->argv_only_cmd[*i]);
		(*i)++;
	}
	if (*j > 0 && ft_strcmp(argv_cpy[*j - 1], "|") != 0)
		argv_cpy[(*j)++] = ft_strdup("|");
	*i = 0;
	while (data->argv_only_cmd[*i])
	{
		if (ft_strcmp(data->argv_only_cmd[*i], "grep") == 0)
		{
			argv_cpy[(*j)++] = ft_strdup("grep");
			if (data->argv_only_cmd[*i + 1])
				argv_cpy[(*j)++] = ft_strdup(data->argv_only_cmd[*i + 1]);
			break ;
		}
		(*i)++;
	}
}

void	rearrange_grep(t_data *data)
{
	char	**argv_cpy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (data->argv_only_cmd[i])
		i++;
	argv_cpy = malloc(sizeof(char *) * (i + 5));
	if (!argv_cpy)
		return ;
	i = 0;
	while_to_cpy(data, &i, &j, argv_cpy);
	argv_cpy[j] = NULL;
	cpy_new_only_cmd(data, argv_cpy);
	free_tab(argv_cpy);
}
