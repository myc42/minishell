/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 02:16:55 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/21 21:40:27 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	two_int_init(int *i, int *j)
{
	*i = 0;
	*j = 0;
}

int	pipe_after_limiter(t_data *data)
{
	int	i;

	i = 0;
	while (data->argv[i])
	{
		if (ft_strncmp(data->argv[i], "<<", 3) == 0)
		{
			if (data->argv[i + 2] && ft_strncmp(data->argv[i + 2], "|", 2) == 0)
				return (1);
		}
		i++;
	}
	return (0);
}

void	cpy_new_here_doc(t_data *data, char **argvcpy)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	if (ft_strncmp(data->here_doc_argv[0], "|", 2) == 0)
		i = 1;
	while (data->here_doc_argv[i])
	{
		if (ft_strncmp(data->here_doc_argv[i], "|", 2) == 0
			&& data->here_doc_argv[i + 1] && ft_strncmp(data->here_doc_argv[i
				+ 1], "|", 2) == 0)
		{
			i++;
			continue ;
		}
		argvcpy[j++] = ft_strdup(data->here_doc_argv[i]);
		i++;
	}
	argvcpy[j] = NULL;
}

void	update_argv_here_doc(t_data *data)
{
	int		i;
	char	**argvcpy;
	int		size_tab;

	i = 0;
	size_tab = 0;
	while (data->here_doc_argv[i])
	{
		if (ft_strncmp(data->here_doc_argv[i], "|", 2) == 0
			&& data->here_doc_argv[i + 1] && ft_strncmp(data->here_doc_argv[i
				+ 1], "|", 2) == 0)
		{
			i++;
			continue ;
		}
		size_tab++;
		i++;
	}
	argvcpy = malloc(sizeof(char *) * (size_tab + 1));
	if (!argvcpy)
	{
		return ;
	}
	cpy_new_here_doc(data, argvcpy);
	free_tab(data->here_doc_argv);
	data->here_doc_argv = argvcpy;
}

int	stock_to_here_doc(t_data *data, int outfilefd)
{
	char	*line;
	int		current;
	int		total;
	size_t	len;

	int_var_stock(&current, &total, data);
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (!line)
			break ;
		len = ft_strlen(data->limiter[current]);
		if (ft_strncmp(line, data->limiter[current], len) == 0
			&& ft_strlen(line) - 1 == len)
		{
			current++;
			free(line);
			if (current == total)
				break ;
			continue ;
		}
		write_outfiled(current, total, outfilefd, line);
	}
	return (0);
}
