/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:22:59 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/14 20:52:55 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_argv_in_tab(t_data *data)
{
	int		i;
	char	**old_argv;
	char	**new_argv;

	old_argv = data->argv;
	if (!old_argv)
		return ;
	i = 0;
	while (old_argv[i])
		i++;
	new_argv = malloc(sizeof(char *) * (i + 1));
	if (!new_argv)
		return ;
	i = 0;
	while (old_argv[i])
	{
		new_argv[i] = normalize_quotes(old_argv[i]);
		i++;
	}
	new_argv[i] = NULL;
	free_tab(old_argv);
	data->argv = new_argv;
}

void	close_signal(t_data *data, int prev_pipe_read_fd, pid_t pid)
{
	if (prev_pipe_read_fd != -1)
		close(prev_pipe_read_fd);
	close_infile_outfile(data, pid);
	signal_and_waitpid(data, pid);
}

void	first_argv_in_tab(t_data *data, char *input, char **env)
{
	int		i;
	char	**av;

	i = 0;
	(void)env;
	av = argv_valid_tab(input);
	if (!av)
		return ;
	data->argv = av;
	update_argv_in_tab(data);
}

void	execute_with_slash(char *cmd, char **argv, char **envp)
{
	execve(cmd, argv, envp);
	perror(cmd);
	if (errno == EACCES || errno == EISDIR)
		exit(126);
	else
		exit(127);
}

void	handle_command_not_found(char **split_cmd)
{
	ft_putstr_fd("command not found\n", 2);
	ft_free_split(split_cmd);
	exit(127);
}
