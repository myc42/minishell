/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_execution.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 20:09:52 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/16 15:42:33 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_eacces_or_isdir(char *cmd_path)
{
	if (cmd_path)
		free(cmd_path);
	exit(126);
}

void	handle_command_not_found2(char **split_cmd, char *cmd_path)
{
	if (cmd_path)
		free(cmd_path);
	if (split_cmd)
		ft_free_split(split_cmd);
	exit(127);
}

void	exe_cmd(t_data *data, int *i, char **envp)
{
	char	**split_cmd;
	char	*cmd_path;
	char	**argv;
	char	*cmd;

	if (!data->argv_pipeline[*i] || !data->argv_pipeline[*i][0])
		return ;
	split_cmd = ft_split(data->argv_pipeline[*i][0], ' ');
	if (!split_cmd || !split_cmd[0])
		return ;
	argv = data->argv_pipeline[*i];
	if (argv && argv[0])
		cmd = argv[0];
	else
		cmd = NULL;
	if (has_slash(cmd))
		execute_with_slash(cmd, argv, envp);
	cmd_path = find_path(envp, split_cmd[0]);
	if (cmd_path == NULL)
		handle_command_not_found(split_cmd);
	execve(cmd_path, data->argv_pipeline[*i], envp);
	if (errno == EACCES || errno == EISDIR)
		handle_eacces_or_isdir(cmd_path);
	handle_command_not_found2(split_cmd, cmd_path);
}

static void	execute_pipelines(t_data *data, int i, int prev_pipe_read_fd,
		int pipeline_nb)
{
	int		fds[2];
	pid_t	pid;

	while (i < pipeline_nb)
	{
		if (i < pipeline_nb - 1)
			pipe_fd(fds);
		ft_forkpid(&pid);
		if (pid == 0)
		{
			reset_signals_child();
			set_input_fd(prev_pipe_read_fd, i, data);
			set_output_fd(i, pipeline_nb, data, fds);
			exe_cmd(data, &i, data->envp);
			exit(EXIT_FAILURE);
		}
		else
		{
			exe_pid_parent(&prev_pipe_read_fd, pipeline_nb, fds, &i);
		}
	}
	free_fds_and_pipelines(data);
	close_signal(data, prev_pipe_read_fd, pid);
}

void	exe(t_data *data)
{
	int	i;
	int	prev_pipe_read_fd;
	int	pipeline_nb;

	init_var_exe(&i, &prev_pipe_read_fd, data, data->input_clean);
	if (!handle_builtin(data))
	{
		if (update_cmd_pipenbr(data, &pipeline_nb))
			execute_pipelines(data, i, prev_pipe_read_fd, pipeline_nb);
	}
	free_fds_and_pipelines(data);
	free_all(data);
}
