/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_execution.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 20:09:52 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/11 19:47:18 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	first_argv_in_tab(t_data *data, char *input)
{
	int		i;
	char	**av;

	i = 0;
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
	// if (!split_cmd[0] || !split_cmd)
	// print_error_and_exit("Error split command");
	cmd_path = find_path(envp, split_cmd[0]);
	if (cmd_path == NULL)
		ft_putstr_fd("command not found: ", 2);
	execve(cmd_path, data->argv_pipeline[*i], envp);
	// print_error_and_exit("execve");
}

void	exe(t_data *data, char *input, int ac, char **env)
{
	int	i;
	

	int		pipeline_nb;
	 pid_t	pid;
	int		status;
	int		fds[2];
	int		prev_pipe_read;
	prev_pipe_read = STDIN_FILENO;
	i = 0;
	first_argv_in_tab(data, input);
	redirect_and_cmds(data, ac, env);
	i = 0;
	pipeline_nb = count_pipeline(data);
	pipeline_nb = count_pipeline(data);
	while (i < pipeline_nb - 1)
	{
		if (i < pipeline_nb - 2)
		{
			if (pipe(data->fd) == -1)
			{
				perror("pipe");
				return ;
			}
		}
		pid = fork();
		if (pid == -1)
		{
			perror("pipe");
			return ;
		}
		if (pid == 0)
		{
			if (i == 0 && data->infile_fd != -1)
			{
				dup2(data->infile_fd, 0);
				close(data->infile_fd);
			}
			else if (prev_pipe_read != STDIN_FILENO)
			{
				dup2(prev_pipe_read, STDIN_FILENO);
				close(prev_pipe_read);
			}
			if (i < pipeline_nb - 1)
			{
				dup2(data->fd[1], 1);
				close(data->fd[0]);
				close(data->fd[1]);
			}
			else
			{
				if (data->outfile_fd != -1)
				{
					dup2(data->outfile_fd, 1);
					close(data->outfile_fd);
				}
			}
			exe_cmd(data, &i, env);
		}
		else
		{
			if (prev_pipe_read != STDIN_FILENO)
				close(prev_pipe_read);
			if (i < count_pipeline(data) - 1)
			{
				close(data->fd[1]);
			
				prev_pipe_read = data->fd[0];
				
			}
			else 
			{
				
				if (data->infile_fd != -1)
					close(data->infile_fd);
				if (data->outfile_fd != -1)
					close(data->outfile_fd);
			}
			waitpid(pid, &status, 0);
		}
		i++;
	}
}
