/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_here_doc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:36:39 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/18 21:25:09 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*read_variable_name(int fd, char first)
{
	char	buffer[100];
	char	c;
	int		i;

	i = 0;
	buffer[i++] = first;
	while (read(fd, &c, 1) > 0 && !ft_isspace(c) && c != '$' && c != '\n')
	{
		if (i < (int)(sizeof(buffer) - 1))
			buffer[i++] = c;
	}
	buffer[i] = '\0';
	return (ft_strdup(buffer));
}

static void	write_expansion(int fdout, char *var_name, t_data *data)
{
	char	*replacement;
	char	*status_str;

	if (var_name[0] == '?' && var_name[1] == '\0')
	{
		status_str = ft_itoa(data->last_status);
		write(fdout, status_str, ft_strlen(status_str));
		free(status_str);
	}
	else
	{
		replacement = search_expansion_replacement(var_name, data);
		if (replacement)
		{
			write(fdout, replacement, ft_strlen(replacement));
			free(replacement);
		}
		else
			write(fdout, var_name, ft_strlen(var_name));
	}
}

static int	handle_dollar(int fdin, int fdout, t_data *data)
{
	char	next;
	char	*var_name;

	if (read(fdin, &next, 1) <= 0)
	{
		write(fdout, "$", 1);
		return (0);
	}
	var_name = read_variable_name(fdin, next);
	write_expansion(fdout, var_name, data);
	free(var_name);
	if (next == '$')
		return (1);
	return (0);
}

void	init_two_int(int *i, char *j)
{
	*i = 0;
	*j = 0;
}

void	expansion_here_doc(int fdin, int fdout, t_data *data)
{
	int		has_pend;
	char	pend_char;
	char	c;

	init_two_int(&has_pend, &pend_char);
	while (1)
	{
		if (has_pend)
		{
			c = pend_char;
			has_pend = 0;
		}
		else if (read(fdin, &c, 1) <= 0)
			break ;
		if (c == '$')
		{
			if (handle_dollar(fdin, fdout, data))
			{
				has_pend = 1;
				pend_char = '$';
			}
		}
		else
			write(fdout, &c, 1);
	}
}
