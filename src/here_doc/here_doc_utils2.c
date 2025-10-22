/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 02:16:55 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/22 02:35:38 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pipe_after_limiter(t_data *data)
{
	int i;

	i = 0;
	while (data->argv[i])
	{
		if (ft_strncmp(data->argv[i], "<<", 3) == 0)
		{
			if (data->argv[i + 2] && ft_strncmp(data->argv[i + 2], "|", 2) == 0)
				return (1);
		}
		i++;
	}
	return (0);
}