/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/11/04 19:27:05 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/04 19:27:05 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_split(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	remove_two_tokens(char **argv, int i)
{
	int	j;

	free(argv[i]);
	free(argv[i + 1]);
	j = i;
	while (argv[j + 2])
	{
		argv[j] = argv[j + 2];
		j++;
	}
	argv[j] = NULL;
	argv[j + 1] = NULL;
}
