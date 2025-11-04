/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_echo_.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:28:34 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/04 18:43:47 by macoulib         ###   ########.fr       */
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

void	remove_two_tokens(char **argv, int i)
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

void	open_dir(char **argv, int i, int *in_fd)
{
	*in_fd = open(argv[i + 1], O_RDONLY);
	if (*in_fd < 0)
	{
		perror(argv[i + 1]);
		exit(1);
	}
	remove_two_tokens(argv, i);
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
			open_dir(argv, i, in_fd);
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
			i++;
	}
}

void	setup_redirections(t_data *data)
{
	int	cmd_count;
	int	i;

	if (!data || !data->argv_pipeline)
		return ;
	cmd_count = ft_count_cmds_pipeline(data);
	data->pipeline_in_fds = malloc(sizeof(int *) * (cmd_count + 1));
	data->pipeline_out_fds = malloc(sizeof(int *) * (cmd_count + 1));
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
	data->pipeline_in_fds[cmd_count] = NULL;
	data->pipeline_out_fds[cmd_count] = NULL;
}
