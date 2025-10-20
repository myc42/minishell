/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:15:41 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/20 04:22:51 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



void	find_cpy_redirect(t_data *data)
{
	char	**rien;

	rien = NULL;
	find_limiter(data);
	alloc_without_limiter(data);
	tab_without_limiter(data);
	cpy_here_doc_argv(data);
	redirect_and_cmds(data, 5, rien);
}

void	stock_to_here_doc(t_data *data, size_t len_lim, int outfilefd)
{
	char	*line;

	while (1)
	{
		write(1, "pipe here_doc > ", 16);
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
	int		outfile;
	size_t	len_lim;
	int		i;

	i = 0;
	find_cpy_redirect(data);
	len_lim = ft_strlen(data->limiter);
	outfile = open("outfilex.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile == -1)
		return (0);
	stock_to_here_doc(data, len_lim, outfile);
	close(outfile);
	outfile = open("outfilex.txt", O_RDONLY);
	if (outfile == -1)
		return (0);
	exe_heredoc(data, outfile);
	return (1);
}
