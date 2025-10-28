/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:15:41 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/26 15:32:59 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	find_cpy_redirect(t_data *data)
{
	find_all_limiters(data);
	alloc_without_limiter(data);
	tab_without_limiter(data);
	cpy_here_doc_argv(data);
	redirect_and_cmds(data);
}
void	stock_to_here_doc(t_data *data, int outfilefd)
{
	char	*line;
	int		current;
	int		total;
	size_t	len;

	total = 0;
	while (data->limiter && data->limiter[total])
		total++;
	current = 0;
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (!line)
			break ;
		len = ft_strlen(data->limiter[current]);
		if (ft_strncmp(line, data->limiter[current], len) == 0
			&& ft_strlen(line) - 1 == len)
		{
			current++;
			free(line);
			if (current == total)
				break ;
			continue ;
		}
		if (current == total - 1)
			write(outfilefd, line, ft_strlen(line));
		free(line);
	}
}

void	run_heredoc_child(t_data *data)
{
	int	outfile;
	int	infile;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);

	find_cpy_redirect(data);
	infile = open(".test2", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (infile == -1)
		exit (1);
	outfile = open(".test", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile == -1)
		exit (1);
	stock_to_here_doc(data, outfile);
	close(outfile);
	outfile = open(".test", O_RDONLY);
	if (outfile == -1)
		exit (1);
	expansion_here_doc(outfile, infile, data);
	close(infile);
	infile = open(".test2", O_RDONLY);
	if (infile == -1)
		exit(1);
	exe_heredoc(data, infile);
	exit(0);	
}


int	builtin_heredoc(t_data *data)
{
	int		status;
	pid_t	pid;
	int	sig;

	pid = fork ();
	if (pid == -1)
	{
		perror("minishell: fork");
		data->last_status = 1;
		return (0);
	}
	if (pid == 0)
	{
		run_heredoc_child(data);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid, &status, 0);
		setup_signals();

		if (WIFSIGNALED (status))
			{
				sig = WTERMSIG(status);
				if (sig == SIGQUIT)
				{
					ft_putstr_fd("Quit (core dumped)\n", 2);
					data->last_status = 130;
				}
				else if (sig == SIGINT)
					ft_putstr_fd("\n", 1);
				data->last_status = 130;
				return (0);
			}
			else
				data->last_status = WEXITSTATUS (status);
	}
	return (1);
}
