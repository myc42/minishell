/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_valid_count.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 23:09:44 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/05 20:02:36 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_variable(int *argv, int *i, int *count, int *s, int *d)
{
	*argv = 0;
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

int	count_argv(char *str)
{
	int	i;
	int	argv;
	int	count;
	int	in_single_quote;
	int	in_double_quote;

	init_variable(&argv, &i, &count, &in_double_quote, &in_single_quote);
	while (str[++i])
	{
		if (str[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (str[i] == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (str[i] == ' ')
			is_word(&argv, &count, in_double_quote, in_single_quote);
		else
		{
			if (!argv)
				argv = !argv;
		}
	}
	if (argv)
		count++;
	return (count);
}
