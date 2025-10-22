/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 22:47:54 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/22 22:48:14 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	t_is_singlequotes(const char *arg)
{
	size_t	len;
	char	first;
	char	last;

	if (arg == NULL || *arg == '\0')
		return (0);
	len = strlen(arg);
	if (len >= 2)
	{
		first = arg[0];
		last = arg[len - 1];
		if (first == '\'' && last == '\'')
			return (1);
	}
	return (0);
}

int	t_is_doublequotes(const char *arg)
{
	size_t	len;
	char	first;
	char	last;

	if (arg == NULL || *arg == '\0')
		return (0);
	len = strlen(arg);
	if (len >= 2)
	{
		first = arg[0];
		last = arg[len - 1];
		if (first == '"' && last == '"')
			return (1);
	}
	return (0);
}

void	clean_quotes(t_data *data)
{
	int i;
	char *strtrimm;

	i = 0;
	while (data->argv[i])
		i++;
	data->argv_clean_quotes = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (data->argv[i])
	{
		if (t_is_singlequotes(data->argv[i]))
		{
			strtrimm = ft_strtrim(data->argv[i], "'");
			data->argv_clean_quotes[i] = ft_strdup(strtrimm);
			free(strtrimm);
		}
		else if (t_is_doublequotes(data->argv[i]))
		{
			strtrimm = ft_strtrim(data->argv[i], "\"");
			data->argv_clean_quotes[i] = ft_strdup(strtrimm);
			free(strtrimm);
		}
		else
			data->argv_clean_quotes[i] = ft_strdup(data->argv[i]);
		i++;
	}
	data->argv_clean_quotes[i] = NULL;
}