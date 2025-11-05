/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_principal.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:04:40 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/05 20:07:22 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*handle_expansion(char *str, int *i, int in_single_quotes,
		t_data *data, char *result)
{
	if (str[*i] == '\'')
	{
		result = append_char(result, str[*i]);
		quotes_and_increment(&in_single_quotes, i);
	}
	else if (str[*i] == '$' && !in_single_quotes)
	{
		(*i)++;
		if (ft_isspace(str[*i]) || !str[*i])
			result = append_dollar_literal(result);
		else
			result = append_variable(str, i, result, data);
	}
	else
		result = append_char(result, str[(*i)++]);
	return (result);
}

char	*expand_variables_in_string(char *str, t_data *data)
{
	int		i;
	int		in_single_quotes;
	char	*result;

	i = 0;
	in_single_quotes = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (str[i])
	{
		result = handle_expansion(str, &i, in_single_quotes, data, result);
		if (!result)
			return (NULL);
	}
	return (result);
}
