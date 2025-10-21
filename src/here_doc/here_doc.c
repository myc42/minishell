/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:15:41 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/21 15:42:17 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	find_cpy_redirect(t_data *data)
{
	find_limiter(data);
	alloc_without_limiter(data);
	tab_without_limiter(data);
	cpy_here_doc_argv(data);
	redirect_and_cmds(data);
}

void	stock_to_here_doc(t_data *data, size_t len_lim, int outfilefd)
{
	char	*line;

	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (!line || (ft_strncmp(line, data->limiter, len_lim) == 0
				&& ft_strlen(line) - 1 == len_lim))
		{
			free(line);
			break ;
		}
		write(outfilefd, line, ft_strlen(line));
		free(line);
	}
}
int	builtin_heredoc(t_data *data)
{
	int	outfile;
	int	i;
	int	infile;

	i = 0;
	find_cpy_redirect(data);
	infile = open(".test2", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (infile == -1)
		return (0);
	outfile = open(".test", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile == -1)
		return (0);
	stock_to_here_doc(data, ft_strlen(data->limiter), outfile);
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
	return (1);
}
