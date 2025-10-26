/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:15:41 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/26 15:25:00 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	int		count;
	int		current_limiter_index;
	size_t	lim_len;

	count = 0;
	while (data->limiter && data->limiter[count])
		count++;
	current_limiter_index = 0;
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (!line)
			break ;
		lim_len = ft_strlen(data->limiter[current_limiter_index]);
		if (ft_strncmp(line, data->limiter[current_limiter_index], lim_len) == 0
			&& ft_strlen(line) - 1 == lim_len)
		{
			if (current_limiter_index == count - 1)
			{
				free(line);
				break ;
			}
			current_limiter_index++;
			free(line);
			continue ;
		}
		if (current_limiter_index == count - 1)
			write(outfilefd, line, ft_strlen(line));
		free(line);
	}
}

int	builtin_heredoc(t_data *data)
{
	int outfile;
	int i;
	int infile;

	i = 0;
	find_cpy_redirect(data);
	infile = open(".test2", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (infile == -1)
		return (0);
	outfile = open(".test", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile == -1)
		return (0);
	stock_to_here_doc(data, outfile);
	close(outfile);
	outfile = open(".test", O_RDONLY);
	if (outfile == -1)
		return (0);
	expansion_here_doc(outfile, infile, data);
	close(infile);
	infile = open(".test2", O_RDONLY);
	if (outfile == -1)
		return (0);
	exe_heredoc(data, infile);
	free(data->limiter);
	return (1);
}