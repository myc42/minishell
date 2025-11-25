/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   biltin3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 20:57:32 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/22 22:05:25 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_cd_error(char *target)
{
	ft_putstr_fd("minishell: cd:  ", 2);
	ft_putstr_fd(target, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

int	is_redirection_operator2(char *token)
{
	if (!token)
		return (0);
	if (!ft_strcmp(token, "<") || !ft_strcmp(token, ">") || !ft_strcmp(token,
			">>") || !ft_strcmp(token, "<<"))
		return (1);
	return (0);
}

void	init_in_out(int *has_in, int *has_out, t_data *data, int i)
{
	*has_in = (data->pipeline_in_fds && data->pipeline_in_fds[i]);
	*has_out = (data->pipeline_out_fds && data->pipeline_out_fds[i]);
}
