/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 23:09:26 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/05 20:00:51 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	int_var_stock(int *current, int *total, t_data *data)
{
	int	x;

	*total = 0;
	x = 0;
	while (data->limiter && data->limiter[x])
		x++;
	*total = x;
	*current = 0;
}

void	write_outfiled(int current, int total, int outfilefd, char *line)
{
	if (current == total - 1)
		write(outfilefd, line, ft_strlen(line));
	free(line);
}

void	find_cpy_redirect(t_data *data)
{
	find_all_limiters(data);
	alloc_without_limiter(data);
	tab_without_limiter(data);
	cpy_here_doc_argv(data);
	redirect_and_cmds(data);
}

void	stock_to_here_doc(t_data *data, int outfilefd)
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
}
