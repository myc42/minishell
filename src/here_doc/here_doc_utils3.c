/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:28:57 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/14 21:00:14 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	if_current_total(t_data *data, int current)
{
	ft_putstr_fd("minishell: here-document delimited by end-of-file `", 2);
	ft_putstr_fd(data->limiter[current], 2);
	ft_putstr_fd("`)\n", 2);
}

void	write_outfiled(int current, int total, int outfilefd, char *line)
{
	if (current == total - 1)
		write(outfilefd, line, ft_strlen(line));
	free(line);
}
