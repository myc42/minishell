/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_in_string.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 19:07:39 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/14 23:04:14 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	quotes_and_increment(int *in_single_quotes, int *i)
{
	*in_single_quotes = !(*in_single_quotes);
	(*i)++;
}

char	*space_or_null_after_sign(char *temp, char *result)
{
	temp = ft_strjoin(result, "$");
	free(result);
	return (temp);
}

char	*copy_normal(char c, char *result, char *temp)
{
	char	char_str[2];

	char_str[0] = c;
	char_str[1] = '\0';
	temp = ft_strjoin(result, char_str);
	free(result);
	return (temp);
}

char	*copy_variable(int *i, char *result, char *temp, t_data *data)
{
	char	*var_name;
	char	*replacement;
	int		j;
	char	*str;

	str = data->temp;
	j = 0;
	while (str[*i + j] && !ft_isspace(str[*i + j]) && str[*i + j] != '\''
		&& str[*i + j] != '"' && str[*i + j] != '$')
		j++;
	var_name = ft_substr(str, *i, j);
	if (!var_name)
		return (NULL);
	replacement = search_expansion_replacement(var_name, data);
	free(var_name);
	if (replacement)
	{
		temp = ft_strjoin(result, replacement);
		free(result);
		free(replacement);
		result = temp;
	}
	*i += j;
	return (result);
}

char	*expand_variables_in_string(char *str, t_data *data)
{
	int		i;
	int		in_single_quotes;
	char	*result;
	char	*temp;

	init_expans_var(&temp, &i, &in_single_quotes, &result);
	alloc_str_for_ex(data, str);
	while (str[i])
	{
		if (str[i] == '\'')
		{
			result = copy_normal(str[i], result, temp);
			quotes_and_increment(&in_single_quotes, &i);
		}
		else if (str[i] == '$' && !in_single_quotes)
		{
			i++;
			if (ft_isspace(str[i]) || !str[i])
				result = space_or_null_after_sign(temp, result);
			else
				result = copy_variable(&i, result, temp, data);
		}
		else
			result = copy_normal(str[i++], result, temp);
	}
	return (result);
}
