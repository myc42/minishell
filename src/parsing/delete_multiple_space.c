/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_multiple_space.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 23:10:39 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/05 20:05:11 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

char	*delete_multiple_space(char *str)
{
	int		i;
	int		j;
	char	*cleaned;

	if (!str)
		return (NULL);
	cleaned = malloc(ft_strlen(str) + 1);
	if (!cleaned)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
		{
			if (j > 0 && !ft_isspace(cleaned[j - 1]))
				cleaned[j++] = ' ';
		}
		else
			cleaned[j++] = str[i];
		i++;
	}
	cleaned[j] = '\0';
	return (cleaned);
}
