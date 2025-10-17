/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:15:41 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/18 00:59:19 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exe_heredoc(t_data *data, int outfile)
{
	//char	**split_cmd;
	//char	*cmd_path;
	pid_t	pid;
	int		pipeline_nb;
	int		prev_pipe_read_fd;
	int		fds[2];
	int		i;
	int status;

	i = 0;
	prev_pipe_read_fd = -1;
	create_pipeline_tab(data);
	pipeline_nb = count_pipeline(data) + 1;
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
			if (prev_pipe_read_fd != -1)
			{
				dup2(prev_pipe_read_fd, 0);
				close(prev_pipe_read_fd);
			}
			else if (i == 0)
			{
				dup2(outfile, 0);
				close(outfile);
			}
			if (i < pipeline_nb - 1)
			{
				close(fds[0]);
				dup2(fds[1], 1);
				close(fds[1]);
			}
			exe_cmd(data, &i, data->envp);
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
		waitpid(pid, &status, 0);
	}
}
int	builtin_heredoc(t_data *data)
{
	int		outfile;
	char	*line;
	size_t	len_lim;
	int		i;

	i = 0;
	find_limiter(data);
	alloc_without_limiter(data);
	tab_without_limiter(data);
	create_pipeline_tab(data);
	len_lim = ft_strlen(data->limiter);
	outfile = open("outfilex.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile == -1)
		return (0);
	while (1)
	{
		line = get_next_line(0);
		if (!line || (ft_strncmp(line, data->limiter, len_lim) == 0
				&& ft_strlen(line) - 1 == len_lim))
		{
			free(line);
			break ;
		}
		write(outfile, line, ft_strlen(line));
		free(line);
	}
	close(outfile);
	outfile = open("outfilex.txt", O_RDONLY);
	if (outfile == -1)
		return (0);
	exe_heredoc(data, outfile);
	return (1);
}
