/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 23:10:21 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/05 17:07:14 by macoulib         ###   ########.fr       */
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
void	data_argv_count_clean(t_data *data, int *i)
{
	*i = 0;
	while (data->argv[*i])
		(*i)++;
}
void	clean_quotes(t_data *data)
{
	int		i;
	char	*strtrimm;

	data_argv_count_clean(data, &i);
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

void	cpy_clean_quotes_to_av(t_data *data)
{
	char **temp_old_argv;

	clean_quotes(data);

	temp_old_argv = data->argv;

	data->argv = data->argv_clean_quotes;

	data->argv_clean_quotes = NULL;

	free_tab(temp_old_argv);
}