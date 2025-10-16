/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:15:41 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/16 23:32:09 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
void	exe_here_doc(t_data *data, int *fd)
{
	int	pipeline_nb;

	(void)fd;
	// int		fds[2];
	// pid_t	pid;
	create_pipeline_tab(data);
	pipeline_nb = count_pipeline(data) + 1;
} */
void	here_doc2(char *limiter, int *fd)
{
	char	*line;
	size_t	len_lim;

	len_lim = ft_strlen(limiter);
	while (1)
	{
		line = get_next_line(0);
		if (!line || (ft_strncmp(line, limiter, len_lim) == 0 && ft_strlen(line)
				- 1 == len_lim))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd[1]);
		free(line);
	}
}

int	builtin_heredoc(t_data *data)
{
	pid_t	pid;
	int		fd[2];

	find_limiter(data);
	alloc_without_limiter(data);
	tab_without_limiter(data);
	char *av = data->argv_only_cmd[0];
	char **argv = data->argv_only_cmd;
	char  **env = data->envp;
	if (pipe(fd) == -1)
		perror("pipe error");
	pid = fork();
	if (pid == -1)
		perror("pid fork error");
	if (!pid)
	{
		close(fd[0]);
		here_doc2(data->limiter, fd);
		execve(av, argv, env);	
		
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		waitpid(pid, NULL, 0);
	}
	return (0);
}
