/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:45:31 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/13 15:49:11 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_parsing(char *str, t_data *data, char **envp)
{
	int	quote;

	(void)envp;
	quote = closed_quotes(str);
	if (!quote)
		return (0);
	if (direction_error(str, data) || *str == 0)
		return (0);
	return (1);
}
