/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_valid_count.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 18:14:03 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/16 22:51:20 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	alloc_str_for_ex(t_data *data, char *str)
{
	data->temp = ft_strdup(str);
	if (!data->temp)
		return ;
}

void	init_variable(int *i, int *count, int *s, int *d)
{
	*i = -1;
	*count = 0;
	*d = 0;
	*s = 0;
}

void	is_word(int *argv, int *count, int s, int d)
{
	if (*argv && !s && !d)
	{
		(*count)++;
		*argv = !*argv;
	}
}

void	init_iint(int *i, int *count, int *doublequotes, int *singlq)
{
	*i = 0;
	*count = 0;
	*doublequotes = 0;
	*singlq = 0;
}

int	count_argv(char *str)
{
	int	i;
	int	count;
	int	in_single_quote;
	int	in_double_quote;

	init_iint(&i, &count, &in_double_quote, &in_single_quote);
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (!str[i])
			break ;
		count++;
		while (str[i])
		{
			if (str[i] == '\'' && !in_double_quote)
				in_single_quote = !in_single_quote;
			else if (str[i] == '\"' && !in_single_quote)
				in_double_quote = !in_double_quote;
			else if (str[i] == ' ' && !in_single_quote && !in_double_quote)
				break ;
			i++;
		}
	}
	return (count);
}
