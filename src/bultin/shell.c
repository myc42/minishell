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

void	start_data(t_data *shell)
{
	char	*input;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			ft_putstr_fd("exit\n", 1);
			break;
		}
		if (*input)
			add_history(input);
		execute_command(input, shell);
		free(input);
	}
}

void	cleanup_shell(t_data *shell)
{
	ft_free_split(shell->envp);
}