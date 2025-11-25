/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:53:50 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/22 22:36:48 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_and_waitpid(t_data *data, pid_t pid)
{
	int		status;
	pid_t	w;

	while (1)
	{
		w = waitpid(pid, &status, 0);
		if (w == -1)
		{
			if (errno == EINTR)
				continue ;
			perror("waitpid");
			status = 1;
			setup_signals();
			return ;
		}
		break ;
	}
	setup_signals();
	update_status_from_signal(status, data);
}

int	check_data_bultin(t_data *data)
{
	if (!data->argv || !data->argv[0])
		return (-1);
	return (0);
}

void	handle_command_not_found2(char **split_cmd, char *cmd_path)
{
	if (cmd_path)
		free(cmd_path);
	if (split_cmd)
		ft_free_split(split_cmd);
	exit(127);
}
