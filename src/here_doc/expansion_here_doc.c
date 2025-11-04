/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_here_doc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 22:54:19 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/04 23:08:14 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ex_here2(t_data *data, char next, int fdin, int fdout)
{
	int		i;
	char	c;
	char	stockage[100];
	char	*resultstockage;

	i = 0;
	stockage[i++] = next;
	while (read(fdin, &c, 1) > 0 && !ft_isspace(c) && c != '$' && c != '\n')
	{
		if (i < (int)(sizeof(stockage) - 1))
			stockage[i++] = c;
	}
	stockage[i] = '\0';
	resultstockage = search_expansion_replacement(stockage, data);
	if (resultstockage)
		write(fdout, resultstockage, ft_strlen(resultstockage));
	else
		write(fdout, stockage, ft_strlen(stockage));
	if (!ft_isspace(c) && c != '\n' && c != '$')
		write(fdout, &c, 1);
	else if (c == '$')
		lseek(fdin, -1, SEEK_CUR);
	else
		write(fdout, &c, 1);
}

void	expansion_here_doc(int fdin, int fdout, t_data *data)
{
	char	c;
	char	next;
	char	*status_str;
	size_t	status_len;

	status_str = ft_itoa(data->last_status);
	status_len = ft_strlen(status_str);
	while (read(fdin, &c, 1) > 0)
	{
		if (c == '$')
		{
			if (read(fdin, &next, 1) > 0)
			{
				if (next == '?')
					write(fdout, status_str, status_len);
				else
					ex_here2(data, next, fdin, fdout);
			}
			else
				write(fdout, &c, 1);
		}
		else
			write(fdout, &c, 1);
	}
	free(status_str);
}
