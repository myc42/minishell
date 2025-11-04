/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 23:10:27 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/04 23:10:29 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../includes/minishell.h"

void	init_variables_to_zero(int *i, int *j, int *s, int *d)
{
	*i = 0;
	*j = 0;
	*s = 0;
	*d = 0;
}

void	pipeline_space(char *str, char *dest)
{
	int	i;
	int	j;
	int	in_single_quote;
	int	in_double_quote;

	init_variables_to_zero(&i, &j, &in_single_quote, &in_double_quote);
	while (str[i])
	{
		if (str[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (str[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		if (str[i] == '|' && !in_single_quote && !in_double_quote)
		{
			if (j > 0 && dest[j - 1] != ' ')
				dest[j++] = ' ';
			dest[j++] = '|';
			if (str[i + 1] && str[i + 1] != ' ')
				dest[j++] = ' ';
		}
		else
			dest[j++] = str[i];
		i++;
	}
	dest[j] = '\0';
}

int	dest_size(char *str)
{
	int	i;
	int	taille;
	int	in_single_quote;
	int	in_double_quote;

	init_variables_to_zero(&i, &taille, &in_single_quote, &in_double_quote);
	while (str[i])
	{
		if (str[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (str[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		if (str[i] == '|' && !in_single_quote && !in_double_quote)
		{
			if (i > 0 && str[i - 1] != ' ')
				taille++;
			taille++;
			if (str[i + 1] && str[i + 1] != ' ')
				taille++;
		}
		else
			taille++;
		i++;
	}
	return (taille + 1);
}


char	*clean_space(char *str)
{
	char	*space_btw_pipeline;
	char	*strtrim;
	char	*final_clean;
	int		bufsize;

	if (!str)
		return (NULL);

	bufsize = dest_size(str);
	space_btw_pipeline = malloc(sizeof(char) * bufsize);
	if (!space_btw_pipeline)
		return (NULL);
	pipeline_space(str, space_btw_pipeline);

	strtrim = ft_strtrim(space_btw_pipeline, " ");
	free(space_btw_pipeline);
	if (!strtrim)
		return (NULL);

	final_clean = delete_multiple_space(strtrim);
	free(strtrim);
	
	return (final_clean);
}
