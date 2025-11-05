/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_in_string.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 23:10:43 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/05 20:06:04 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	free_s1s2(free_s1, free_s2, s1, s2);
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
	while (str[*i + j] && !ft_isspace(str[*i + j]) && str[*i + j] != '\''
		&& str[*i + j] != '"' && str[*i + j] != '$')
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
