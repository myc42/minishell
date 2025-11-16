/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:15:41 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/16 22:30:59 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	setup_heredoc_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handle_sigint_heredoc;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	run_heredoc_child(t_data *data)
{
	int	outfile;
	int	infile;
	int	code;
	int	prev_pipe_read_fd;

	find_cpy_redirect(data);
	infile = open(".test2", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (infile == -1)
		exit(1);
	outfile = open(".test", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile == -1)
		exit(1);
	code = stock_to_here_doc(data, outfile);
	close(outfile);
	outfile = open(".test", O_RDONLY);
	if (outfile == -1)
		exit(1);
	expansion_here_doc(outfile, infile, data);
	close(infile);
	infile = open(".test2", O_RDONLY);
	if (infile == -1)
		exit(1);
	exe_heredoc(data, infile, &prev_pipe_read_fd);
	close(outfile);
	exit(code);
}

void	find_cpy_redirect(t_data *data)
{
	setup_heredoc_signals();
	find_all_limiters(data);
	alloc_without_limiter(data);
	tab_without_limiter(data);
	cpy_here_doc_argv(data);
	redirect_and_cmds(data, 1);
}

int	bultin2(t_data *data, pid_t pid, int status, int sig)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	setup_signals();
	if (WIFSIGNALED(status))
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
		data->last_status = WEXITSTATUS(status);
	return (0);
}
