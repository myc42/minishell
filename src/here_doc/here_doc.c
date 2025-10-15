/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:15:41 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/15 19:46:17 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	int		outfile;
	pid_t	pid;
	int		fd[2];

	outfile = open("here_doc_tmp", O_WRONLY | O_CREAT | O_APPEND, 0644);
	find_limiter(data);
	alloc_without_liniter(data);
	tab_without_limiter(data);
	if (pipe(fd) == -1)
		perror("pipe error");
	pid = fork();
	if (pid == -1)
		perror("pid fork error");
	if (!pid)
	{
		close(fd[0]);
		here_doc2(data->limiter, fd);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		waitpid(pid, NULL, 0);
	}
	
	return (0);
}
