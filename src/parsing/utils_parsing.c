/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:02:17 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/05 20:08:56 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	three_variable_init(int *i, int *j, int *k)
{
	*i = 0;
	*j = 0;
	*k = 0;
}

void	quotes_and_increment(int *in_single_quotes, int *i)
{
	*in_single_quotes = !(*in_single_quotes);
	(*i)++;
}

void	free_s1s2(int free_s1, int free_s2, char *s1, char *s2)
{
	if (free_s1)
		free(s1);
	if (free_s2)
		free(s2);
}
