/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_echo_.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:28:34 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/16 21:07:20 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	init_var_setupredirec(t_data *data, int *cmd_count)
{
	*cmd_count = ft_count_cmds_pipeline(data);
	data->pipeline_in_fds = malloc(sizeof(int *) * (*cmd_count + 1));
	data->pipeline_out_fds = malloc(sizeof(int *) * (*cmd_count + 1));
	data->pipeline_err_fds = malloc(sizeof(int *) * (*cmd_count + 1));
	if (!data->pipeline_in_fds || !data->pipeline_out_fds
		|| !data->pipeline_err_fds)
	{
		return (0);
	}
	return (1);
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

static void	handle_redirection(char **argv, int *i, int *fd, int flags)
{
	*fd = open(argv[*i + 1], flags, 0644);
	remove_two_tokens(argv, *i);
}

int	analyze_redirections(char **argv, int *in_fd, int *out_fd, int *err_fd)
{
	int	i;

	i = 0;
	*in_fd = STDIN_FILENO;
	*out_fd = STDOUT_FILENO;
	*err_fd = STDERR_FILENO;
	while (argv[i])
	{
		if (ft_strcmp(argv[i], "<") == 0 && argv[i + 1])
			open_dir(argv, i, in_fd);
		else if (ft_strcmp(argv[i], ">") == 0 && argv[i + 1])
			handle_redirection(argv, &i, out_fd, O_WRONLY | O_CREAT | O_TRUNC);
		else if (ft_strcmp(argv[i], ">>") == 0 && argv[i + 1])
			handle_redirection(argv, &i, out_fd, O_WRONLY | O_CREAT | O_APPEND);
		else if (ft_strcmp(argv[i], "2>") == 0 && argv[i + 1])
			handle_redirection(argv, &i, err_fd, O_WRONLY | O_CREAT | O_TRUNC);
		else if (ft_strcmp(argv[i], "2>>") == 0 && argv[i + 1])
			handle_redirection(argv, &i, err_fd, O_WRONLY | O_CREAT | O_APPEND);
		else
			i++;
	}
	return (1);
}

void	setup_redirections(t_data *data)
{
	int	cmd_count;
	int	i;

	if (!data || !data->argv_pipeline)
		return ;
	if (!init_var_setupredirec(data, &cmd_count))
		return ;
	i = 0;
	while (i < cmd_count)
	{
		data->pipeline_in_fds[i] = malloc(sizeof(int));
		data->pipeline_out_fds[i] = malloc(sizeof(int));
		data->pipeline_err_fds[i] = malloc(sizeof(int));
		if (!data->pipeline_in_fds[i] || !data->pipeline_out_fds[i]
			|| !data->pipeline_err_fds[i])
			return ;
		analyze_redirections(data->argv_pipeline[i], data->pipeline_in_fds[i],
			data->pipeline_out_fds[i], data->pipeline_err_fds[i]);
		i++;
	}
	data->pipeline_in_fds[cmd_count] = NULL;
	data->pipeline_out_fds[cmd_count] = NULL;
	data->pipeline_err_fds[cmd_count] = NULL;
}
