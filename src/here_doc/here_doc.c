/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:15:41 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/17 23:19:03 by macoulib         ###   ########.fr       */
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


int	builtin_heredoc(t_data *data)
{
	
	int		outfile;
	char	*line;
	size_t	len_lim;
	pid_t	pid;
	char	**split_cmd;
	char	*cmd_path;
	
	find_limiter(data);
	alloc_without_limiter(data);
	tab_without_limiter(data);
	len_lim = ft_strlen(data->limiter);
	
	outfile = open("outfilex.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile == -1)
			return(0);
	split_cmd = ft_split(data->argv_only_cmd[0], ' ');
	cmd_path = find_path(data->envp, split_cmd[0]);
	if (cmd_path == NULL)
	{
		ft_putstr_fd("command not found: \n", 2);
		exit(127);
	}
	
	while (1)
	{
		line = get_next_line(0);
		if (!line || (ft_strncmp(line, data->limiter, len_lim) == 0 && ft_strlen(line)
				- 1 == len_lim))
		{
			free(line);
			break ;
		}
		write(outfile,line,ft_strlen(line));
		free(line);
	}
	close (outfile) ;
	outfile = open("outfilex.txt", O_RDONLY);
	if (outfile == -1)
			return(0);
	pid = fork();
	if(pid == -1)
		return (0);
	if(pid == 0)
	{
		dup2(outfile,0);
		execve(cmd_path, data->argv_only_cmd, data->envp);
	}else 
	{
		waitpid(pid, NULL, 0);
	}
	
	return (0);
}
