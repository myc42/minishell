/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:42:54 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/14 21:14:58 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	redirection_detected(char **av)
{
	int	i;

	i = 0;
	while (av && av[i])
	{
		if (!ft_strcmp(av[i], ">") || !ft_strcmp(av[i], "<")
			|| !ft_strcmp(av[i], ">>") || !ft_strcmp(av[i], "<<")
			|| !ft_strcmp(av[i], "2>"))
			return (1);
		i++;
	}
	return (0);
}

int	is_redirection_operator(char *av)
{
	if (ft_strcmp(av, "<") == 0 || ft_strcmp(av, ">") == 0 || ft_strcmp(av,
			">>") == 0 || ft_strcmp(av, "<<") == 0 || ft_strcmp(av, "2>") == 0)
		return (1);
	return (0);
}
