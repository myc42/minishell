/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:38:31 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/14 17:38:31 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../includes/minishell.h"

void init_data(t_data *data, char **envp)
{
	data->envp = copy_envp(envp);
	data->last_status =0;
	if (!data->envp)
	{
		ft_putstr_fd("Error: env copy failed\n", 2);
		exit(1);
	}
	setup_signals();
}
