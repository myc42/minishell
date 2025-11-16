/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 20:26:15 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/14 21:19:00 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*normalize_quotes(char *str)
{
	int		i;
	int		j;
	char	*result;
	char	quote;

	two_int_init(&i, &j);
	result = malloc(ft_strlen(str) + 1);
	quote = 0;
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && quote == 0)
		{
			quote = str[i];
			i++;
			continue ;
		}
		else if (str[i] == quote)
		{
			quote = 0;
			i++;
			continue ;
		}
		result[j++] = str[i++];
	}
	return (result[j] = '\0', result);
}
