/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 20:33:45 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/04 20:34:42 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_directions_on_tab(t_data *data)
{
	int	i;

	i = 0;
	while (data->argv[i])
	{
		if (is_redirection_operator(data->argv[i]) && data->argv[i + 1]
			&& is_redirection_operator(data->argv[i + 1]))
		{
			ft_putstr_fd("syntax error near unexpected token `", 2);
			ft_putstr_fd(data->argv[i + 1], 2);
			ft_putstr_fd("'\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

void	close_signal(t_data *data, int prev_pipe_read_fd, pid_t pid)
{
	if (prev_pipe_read_fd != -1)
		close(prev_pipe_read_fd);
	close_infile_outfile(data, pid);
	signal_and_waitpid(data, pid);
}

void	if_cmd_inexistant(char **argv_exec)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(argv_exec[0], 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	if_after_exeve(char *cmd_path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_path, 2);
	ft_putstr_fd(": ", 2);
	perror(NULL);
	free(cmd_path);
}