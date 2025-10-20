/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_execution.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 20:09:52 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/20 02:44:53 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	first_argv_in_tab(t_data *data, char *input, char **env)
{
	int		i;
	char	**av;
	char	*expan;
	char	*mult_space;

	i = 0;
	mult_space = clean_space(input);
	expan = expand_variables_in_string(mult_space, env);
	av = argv_valid_tab(expan);
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

void	exe(t_data *data, char *input, int ac, char **env)
{
	int		i;
	int		pipeline_nb;
	int		prev_pipe_read_fd;
	int		fds[2];
	pid_t	pid;
	int		status;

	i = 0;
	prev_pipe_read_fd = -1;
	first_argv_in_tab(data, input, env);
	if (!handle_builtin(data))
	{
		redirect_and_cmds(data, ac, env);
		pipeline_nb = count_pipeline(data) + 1 ;
		while (i < pipeline_nb)
		{
			if (i < pipeline_nb - 1)
			{
				if (pipe(fds) == -1)
				{
					perror("pipe");
					return ;
				}
			}
			pid = fork();
			if (pid == -1)
				return ;
			if (pid == 0)
			{
				reset_signals_child();
				if (prev_pipe_read_fd != -1)
				{
					dup2(prev_pipe_read_fd, 0);
					close(prev_pipe_read_fd);
				}
				else if (i == 0 && data->infile_fd != -1)
				{
					dup2(data->infile_fd, 0);
					close(data->infile_fd);
				}
				if (i < pipeline_nb - 1)
				{
					close(fds[0]);
					dup2(fds[1], 1);
					close(fds[1]);
				}
				else if (data->outfile_fd != -1)
				{
					dup2(data->outfile_fd, 1);
					close(data->outfile_fd);
				}
				exe_cmd(data, &i, env);
				exit(EXIT_FAILURE);
			}
			else
			{
				if (prev_pipe_read_fd != -1)
					close(prev_pipe_read_fd);
				if (i < pipeline_nb - 1)
				{
					prev_pipe_read_fd = fds[0];
					close(fds[1]);
				}
				else
				{
					prev_pipe_read_fd = -1;
				}
				i++;
			}
			if (data->infile_fd != -1)
				close(data->infile_fd);
			if (data->outfile_fd != -1)
				close(data->outfile_fd);
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			waitpid(pid, &status, 0);
			setup_signals();
			update_status_from_signal(status, data);
		}
	}
}
