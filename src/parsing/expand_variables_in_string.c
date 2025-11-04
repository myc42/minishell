/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_in_string.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 23:10:43 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/04 23:10:44 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../includes/minishell.h"

void	quotes_and_increment(int *in_single_quotes, int *i)
{
	*in_single_quotes = !(*in_single_quotes);
	(*i)++;
}

char	*ft_strjoin_free(char *s1, char *s2, int free_s1, int free_s2)
{
	char	*join;
	char	*left;
	char	*right;

	if (s1)
		left = s1;
	else
		left = "";
	if (s2)
		right = s2;
	else
		right = "";

	join = ft_strjoin(left, right);
	if (!join)
	{
		if (free_s1)
			free(s1);
		if (free_s2)
			free(s2);
		return (NULL);
	}
	if (free_s1)
		free(s1);
	if (free_s2)
		free(s2);
	return (join);
}


char	*append_char(char *result, char c)
{
	char	char_str[2];
	char	*new_result;

	char_str[0] = c;
	char_str[1] = '\0';
	new_result = ft_strjoin_free(result, char_str, 1, 0); 
	return (new_result);
}


char	*append_dollar_literal(char *result)
{
	char	*new_result;

	new_result = ft_strjoin(result, "$");
	free(result);
	return (new_result);
}

char	*append_variable(char *str, int *i, char *result, t_data *data)
{
	int		j;
	char	*var_name;
	char	*replacement;
	char	*new_result;

	j = 0;
	while (str[*i + j] && !ft_isspace(str[*i + j])
		&& str[*i + j] != '\'' && str[*i + j] != '"'
		&& str[*i + j] != '$')
		j++;
	var_name = ft_substr(str, *i, j);
	if (!var_name)
		return (result);
	replacement = search_expansion_replacement(var_name, data);
	free(var_name);
	if (!replacement)
		replacement = ft_strdup("");
	new_result = ft_strjoin(result, replacement);
	free(result);
	free(replacement);
	*i += j;
	return (new_result);
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
		if (str[i] == '\'')
		{
			result = append_char(result, str[i]);
			quotes_and_increment(&in_single_quotes, &i);
		}
		else if (str[i] == '$' && !in_single_quotes)
		{
			i++;
			if (ft_isspace(str[i]) || !str[i])
				result = append_dollar_literal(result);
			else
				result = append_variable(str, &i, result, data);
		}
		else
			result = append_char(result, str[i++]);
		if (!result)
			return (NULL);
	}
	return (result);
}
