/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_execution.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 20:09:52 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/29 23:30:07 by macoulib         ###   ########.fr       */
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
	char	*expan;
	char	*mult_space;
	int		size;

	(void)env;
	mult_space = clean_space(input);
	expan = expand_variables_in_string(mult_space, data);
	av = argv_valid_tab(expan);
	free(mult_space);
	free(expan);
	if (!av)
		return ;
	size = 0;
	while (av[size])
		size++;
	data->argv = malloc(sizeof(char *) * (size + 1));
	if (!data->argv)
		return (free_tab(av));
	i = 0;
	while (av[i])
	{
		data->argv[i] = ft_strdup(av[i]);
		i++;
	}
	data->argv[i] = NULL;
	free_tab(av);
}

void	exe_cmd(t_data *data, int *i, char **envp)
{
	char	**argv_exec;
	char	*cmd_path;
	int		has_slash;

	if (data->argv_pipeline && data->argv_pipeline[*i])
		argv_exec = data->argv_pipeline[*i];
	else
		argv_exec = data->argv;
	if (!argv_exec || !argv_exec[0])
	{
		ft_putstr_fd("minishell: empty command\n", 2);
		exit(127);
	}
	has_slash = (ft_strchr(argv_exec[0], '/') != NULL);
	if (has_slash)
		cmd_path = ft_strdup(argv_exec[0]);
	else
		cmd_path = find_path(envp, argv_exec[0]);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(argv_exec[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	execve(cmd_path, argv_exec, envp);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_path, 2);
	ft_putstr_fd(": ", 2);
	perror(NULL);
	free(cmd_path);
	if (errno == ENOENT)
		exit(127);
	exit(126);
}

void	exe(t_data *data, char *input, char **env)
{
	int		i;
	int		pipeline_nb;
	int		prev_pipe_read_fd;
	int		fds[2];
	pid_t	pid;

	init_var_exe(&i, &prev_pipe_read_fd, data, input, env);
	if (handle_builtin(data))
		return ;
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
	free_all(data);
}
