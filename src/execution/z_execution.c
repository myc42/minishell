/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_execution.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 20:09:52 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/23 22:53:14 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	while (av[i])
		i++;
	data->argv = malloc(sizeof(char *) * (i + 1));
	if (!data->argv)
		return ;
	i = 0;
	while (av[i])
	{
		data->argv[i] = ft_strdup(av[i]);
		i++;
	}
	data->argv[i] = NULL;
}

void	exe_cmd(t_data *data, int *i, char **envp)
{
	char	**split_cmd;
	char	*cmd_path;

	split_cmd = ft_split(data->argv_pipeline[*i][0], ' ');
	if (!split_cmd[0] || !split_cmd)
	{
		ft_putstr_fd("Error split command: ", 2);
		return ;
	}
	cmd_path = find_path(envp, split_cmd[0]);
	if (cmd_path == NULL)
	{
		ft_putstr_fd("command not found: \n", 2);
		exit(127);
	}
	execve(cmd_path, data->argv_pipeline[*i], envp);
}

void	exe(t_data *data, char *input, char **env)
{
	int		i;
	int		pipeline_nb;
	int		prev_pipe_read_fd;
	int		fds[2];
	pid_t	pid;

	init_var_exe(&i, &prev_pipe_read_fd, data, input, env);
	if (!handle_builtin(data))
	{
		update_cmd_pipenbr(data, &pipeline_nb);
		while (i < pipeline_nb)
		{
			if (i < pipeline_nb - 1)
				pipe_fd(fds);
			ft_forkpid(&pid);
			if (pid == 0)
			{
				exe_pid_zero_one(prev_pipe_read_fd, i, data, pipeline_nb, fds);
				exe_cmd(data, &i, env);
				exit(EXIT_FAILURE);
			}
			else
				exe_pid_parent(&prev_pipe_read_fd, pipeline_nb, fds, &i);
		}
		close_signal(data, prev_pipe_read_fd, pid);
	}
	free_all(data);
}
