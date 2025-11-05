/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_execution.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 19:56:13 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/05 00:08:12 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


char	**init_argv_exec(t_data *data, int *i)
{
	char	**argv_exec;

	if (data->argv_pipeline && data->argv_pipeline[*i])
		argv_exec = data->argv_pipeline[*i];
	else
		argv_exec = data->argv;
	if (!argv_exec || !argv_exec[0])
	{
		ft_putstr_fd("minishell: empty command\n", 2);
		return (NULL);
	}
	return (argv_exec);
}

void	exe_cmd(t_data *data, int *i, char **envp)
{
	char	**argv_exec;
	char	*cmd_path;
	int		has_slash;

	argv_exec = init_argv_exec(data, i);
	if (!argv_exec)
		exit(127);
	has_slash = (ft_strchr(argv_exec[0], '/') != NULL);
	if (has_slash)
		cmd_path = ft_strdup(argv_exec[0]);
	else
		cmd_path = find_path(envp, argv_exec[0]);
	if (!cmd_path)
	{
		if_cmd_inexistant(argv_exec);
		exit(127);
	}
	execve(cmd_path, argv_exec, envp);
	if_after_exeve(cmd_path);
	free_tab(data->argv);
	if (errno == ENOENT)
		exit(127);
	exit(126);
}

int	process_pre_execution(t_data *data, int *pipeline_nb)
{
	if (check_directions_on_tab(data))
		return (1);
	if (handle_builtin(data))
		return (1);
	if (!update_cmd_pipenbr(data, pipeline_nb))
		return (1);
	return (0);
}

void	exe(t_data *data, char *input, char **env)
{
	int		i;
	int		pipeline_nb;
	int		prev_pipe_read_fd;
	int		fds[2];
	pid_t	pid;

	init_var_exe(&i, &prev_pipe_read_fd, data, input, env);
	if (process_pre_execution(data, &pipeline_nb))
		return ;
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
	free_all(data);
}
