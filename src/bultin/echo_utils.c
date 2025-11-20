/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 19:23:03 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/20 20:09:03 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pid_zero_one(t_data *data, int i, int *pipefd, int infile_fd)
{
	int	cmd_count;
	int	has_in;
	int	has_out;

	cmd_count = ft_count_cmds_pipeline(data);
	if (cmd_count == 0)
		cmd_count = 1;
	has_in = (data->pipeline_in_fds && data->pipeline_in_fds[i]);
	has_out = (data->pipeline_out_fds && data->pipeline_out_fds[i]);
	if (i == 0 && infile_fd != -1)
		dup2(infile_fd, STDIN_FILENO);
	else if (has_in && *(data->pipeline_in_fds[i]) != STDIN_FILENO)
		dup2(*(data->pipeline_in_fds[i]), STDIN_FILENO);
	else if (data->outfile_fd != -1)
		dup2(data->outfile_fd, STDIN_FILENO);
	if (has_out && *(data->pipeline_out_fds[i]) != STDOUT_FILENO)
		dup2(*(data->pipeline_out_fds[i]), STDOUT_FILENO);
	else if (i < cmd_count - 1)
		dup2(pipefd[1], STDOUT_FILENO);
	if (data->outfile_fd != -1)
		close(data->outfile_fd);
	if (i < cmd_count - 1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

void	wait_management(int cmd_count)
{
	int	i;

	i = 0;
	while (i++ < cmd_count)
		wait(NULL);
}

void	exe_end(int *prev_fd, int *pipefd, int cmd_count, int i)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (i < cmd_count - 1)
		close(pipefd[1]);
	if (i < cmd_count - 1)
		*prev_fd = pipefd[0];
	else
		*prev_fd = -1;
}

void	init_var_ex_pip(int *prev_fd, int *i)
{
	*prev_fd = -1;
	*i = -1;
}

void	execute_pipeline(t_data *data, int infile_fd)
{
	int		cmd_count;
	int		prev_fd;
	pid_t	pid;
	int		pipefd[2];
	int		i;

	init_pipeline_and_fd(data, &cmd_count, pipefd);
	init_var_ex_pip(&prev_fd, &i);
	while (++i < cmd_count)
	{
		if (i < cmd_count - 1 && pipe(pipefd) == -1)
			exit(1);
		pid = fork();
		if (pid == -1)
			exit(1);
		if (pid == 0)
		{
			pid_zero_one(data, i, pipefd, infile_fd);
			exe_cmd(data, &i, data->envp);
			perror("execvp");
			exit(1);
		}
		exe_end(&data->outfile_fd, pipefd, cmd_count, i);
	}
	wait_management(cmd_count);
}
