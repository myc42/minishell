/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 01:41:39 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/29 17:50:10 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_count_cmds_pipeline(t_data *data)
{
	int	count;

	count = 0;
	if (!data || !data->argv_pipeline)
		return (0);
	while (data->argv_pipeline[count] != NULL)
		count++;
	return (count);
}

static void	remove_two_tokens(char **argv, int i)
{
	int	j;

	free(argv[i]);
	free(argv[i + 1]);
	j = i;
	while (argv[j + 2])
	{
		argv[j] = argv[j + 2];
		j++;
	}
	argv[j] = NULL;
	argv[j + 1] = NULL;
}

void	analyze_redirections(char **argv, int *in_fd, int *out_fd)
{
	int	i;

	i = 0;
	*in_fd = STDIN_FILENO;
	*out_fd = STDOUT_FILENO;
	while (argv[i])
	{
		if (strcmp(argv[i], "<") == 0 && argv[i + 1])
		{
			*in_fd = open(argv[i + 1], O_RDONLY);
			if (*in_fd < 0)
			{
				perror(argv[i + 1]);
				exit(1);
			}
			remove_two_tokens(argv, i);
		}
		else if (strcmp(argv[i], ">") == 0 && argv[i + 1])
		{
			*out_fd = open(argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			remove_two_tokens(argv, i);
		}
		else if (strcmp(argv[i], ">>") == 0 && argv[i + 1])
		{
			*out_fd = open(argv[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			remove_two_tokens(argv, i);
		}
		else
		{
			i++;
		}
	}
}

void	setup_redirections(t_data *data)
{
	int	cmd_count;
	int	i;

	if (!data || !data->argv_pipeline)
		return ;
	cmd_count = ft_count_cmds_pipeline(data);
	data->pipeline_in_fds = malloc(sizeof(int *) * cmd_count);
	data->pipeline_out_fds = malloc(sizeof(int *) * cmd_count);
	if (!data->pipeline_in_fds || !data->pipeline_out_fds)
		return ;
	i = 0;
	while (i < cmd_count)
	{
		data->pipeline_in_fds[i] = malloc(sizeof(int));
		data->pipeline_out_fds[i] = malloc(sizeof(int));
		if (!data->pipeline_in_fds[i] || !data->pipeline_out_fds[i])
			return ;
		analyze_redirections(data->argv_pipeline[i], data->pipeline_in_fds[i],
			data->pipeline_out_fds[i]);
		i++;
	}
}
void	execute_pipeline(t_data *data)
{
	int		cmd_count;
	int		prev_fd;
	pid_t	pid;
		int pipefd[2] = {-1, -1};

	cmd_count = ft_count_cmds_pipeline(data);
	prev_fd = -1;
	for (int i = 0; i < cmd_count; i++)
	{
		if (i < cmd_count - 1)
		{
			if (pipe(pipefd) == -1)
			{
				perror("pipe");
				exit(1);
			}
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(1);
		}
		if (pid == 0)
		{
			if (*(data->pipeline_in_fds[i]) != STDIN_FILENO)
			{
				dup2(*(data->pipeline_in_fds[i]), STDIN_FILENO);
			}
			else if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
			}
			if (*(data->pipeline_out_fds[i]) != STDOUT_FILENO)
			{
				dup2(*(data->pipeline_out_fds[i]), STDOUT_FILENO);
			}
			else if (i < cmd_count - 1)
			{
				dup2(pipefd[1], STDOUT_FILENO);
			}
			if (prev_fd != -1)
				close(prev_fd);
			if (i < cmd_count - 1)
			{
				close(pipefd[0]);
				close(pipefd[1]);
			}
			execvp(data->argv_pipeline[i][0], data->argv_pipeline[i]);
			perror("execvp");
			exit(1);
		}
		if (prev_fd != -1)
			close(prev_fd);
		if (i < cmd_count - 1)
			close(pipefd[1]);
		prev_fd = (i < cmd_count - 1) ? pipefd[0] : -1;
	}
	for (int i = 0; i < cmd_count; i++)
		wait(NULL);
}

int	exe_echox(t_data *data)
{
	ft_split_by_pipe(data);
	setup_redirections(data);
	execute_pipeline(data);

	return (1);
}