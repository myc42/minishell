/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:45:43 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/16 16:06:43 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*clean_parenthese(char *str)
{
	size_t	start;
	size_t	i;
	size_t	end;

	if (!str)
		return (NULL);
	start = 0;
	i = 0;
	end = ft_strlen(str);
	while (str[start] && ft_isspace((unsigned char)str[start]))
		start++;
	while (end > start && ft_isspace((unsigned char)str[end - 1]))
		end--;
	if (end > start && str[start] == '(' && str[end - 1] == ')')
	{
		while (start + 1 + i < end - 1)
		{
			str[i] = str[start + 1 + i];
			i++;
		}
		str[i] = '\0';
	}
	return (str);
}

int	is_separator(char *str)
{
	return (!ft_strcmp(str, ">") || !ft_strcmp(str, ">>") || !ft_strcmp(str,
			"<") || !ft_strcmp(str, "|"));
}

int	check_after_redirection(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (is_separator(av[i]))
		{
			if (av[i + 1] == NULL || is_separator(av[i + 1]))
				return (1);
		}
		i++;
	}
	return (0);
}

int	direction_error(char *str, t_data *data)
{
	int	i;
	int	j;

	i = ft_strlen(str) - 1;
	j = 0;
	(void)data;
	while (i >= 0 && (str[i] == ' ' || str[i] == '\t'))
		i--;
	if (i >= 0 && (str[i] == '|' || str[i] == '>' || str[i] == '<'))
	{
		return (1);
	}
	return (0);
}

int	check_if_is_only_space(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}
