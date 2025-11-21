/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_execution.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 20:09:52 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/21 22:37:37 by macoulib         ###   ########.fr       */
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

/*void	exe_cmd(t_data *data, int *i, char **envp)
{
	char	**split_cmd;
	char	*cmd_path;
	char	**argv;
	char	*cmd;
	char	**saved_argv;
	int		status;

	if (!data->argv_pipeline[*i] || !data->argv_pipeline[*i][0])
		return ;

	saved_argv = data->argv;
	data->argv = data->argv_pipeline[*i];
	status = execute_builtin(data);
	data->argv = saved_argv;
	if (status != -1)
	{
		exit(status);
	}

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
}*/

int execute_builtin_in_child(t_data *data)
{
    int i;

    i = 0;
    if (!data->argv || !data->argv[0])
        return (-1);

    if (ft_strncmp(data->argv[0], "pwd", 4) == 0)
        return (builtin_pwd());
    if (ft_strncmp(data->argv[0], "echo", 5) == 0)
        return (bult_echo(data));
    if (ft_strncmp(data->argv[0], "cd", 3) == 0)
        return (builtin_cd(data, data->envp));
    if (ft_strncmp(data->argv[0], "env", 4) == 0)
        return (builtin_env(data->envp));
    if (ft_strncmp(data->argv[0], "export", 7) == 0)
        return (builtin_export(data->argv, &data->envp));
    if (ft_strncmp(data->argv[0], "unset", 6) == 0)
        return (builtin_unset(data->argv, &data->envp));
    if (ft_strncmp(data->argv[0], "exit", 5) == 0)
        return (builtin_exit(data));

    while (data->argv[i])
    {
        if (ft_strncmp(data->argv[i], "<<", 3) == 0)
            return (builtin_heredoc(data));
        i++;
    }
    return (-1);
}


void exe_cmd(t_data *data, int *i, char **envp)
{
    char    **split_cmd;
    char    *cmd_path;
    char    **argv;
    char    *cmd;
    char    **saved_argv;
    int     status;

    if (!data->argv_pipeline[*i] || !data->argv_pipeline[*i][0])
        return;
	
    saved_argv = data->argv;
    data->argv = data->argv_pipeline[*i];
    status = execute_builtin_in_child(data);
    data->argv = saved_argv;
    if (status != -1)
        exit(status);

    split_cmd = ft_split(data->argv_pipeline[*i][0], ' ');
    if (!split_cmd || !split_cmd[0])
        return;

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


void	execute_pipelines(t_data *data, int i, int prev_pipe_read_fd,
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
	first_argv_in_tab(data, data->input_clean, data->envp);
	if (check_redirect_slash(data))
		return ;
	if (!detect_bad_input(data->argv))
		return ;
	if (!handle_builtin(data))
	{
		cpy_clean_quotes_to_av(data);
		ft_split_by_pipe(data);
		setup_redirections(data);
		if(data->argv_pipeline[0][0])
			execute_pipeline(data, -1);
		free_pipeline_fds(data);
		free_argv_pipeline(data);
	}
}
