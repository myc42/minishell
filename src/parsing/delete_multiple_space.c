/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_multiple_space.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 19:07:33 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/24 15:32:50 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
	{
		return (1);
	}
	return (0);
}

void	copy_n_delete(char *str, char *correct_str, int in_single_quote,
		int in_double_quote)
{
	int	i;
	int	j;

	init_variables_to_zero(&i, &j, &in_single_quote, &in_double_quote);
	while (str[i])
	{
		if (str[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (str[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		if (!in_single_quote && !in_double_quote)
		{
			if (ft_isspace(str[i]))
			{
				if (j > 0 && !ft_isspace(correct_str[j - 1]))
					correct_str[j++] = ' ';
			}
			else
				correct_str[j++] = str[i];
		}
		else
			correct_str[j++] = str[i];
		i++;
	}
	correct_str[j] = '\0';
}

char	*delete_multiple_space(char *str)
{
	int		i;
	int		j;
	int		in_single_quote;
	int		in_double_quote;
	char	*correct_str;

	i = 0;
	j = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	correct_str = malloc(ft_strlen(str) + 1);
	if (!correct_str)
		return (NULL);
	copy_n_delete(str, correct_str, in_single_quote, in_double_quote);
	return (correct_str);
}
