/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 23:09:30 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/05 19:56:52 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	run_heredoc_child(t_data *data)
{
	int	outfile;
	int	infile;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	find_cpy_redirect(data);
	infile = open(".test2", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (infile == -1)
		exit(1);
	outfile = open(".test", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile == -1)
		exit(1);
	stock_to_here_doc(data, outfile);
	close(outfile);
	outfile = open(".test", O_RDONLY);
	if (outfile == -1)
		exit(1);
	expansion_here_doc(outfile, infile, data);
	close(infile);
	infile = open(".test2", O_RDONLY);
	if (infile == -1)
		exit(1);
	exe_heredoc(data, infile);
	exit(0);
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

int	wait_and_handle_heredoc(t_data *data, pid_t pid)
{
	int	status;
	int	sig;

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
	{
		data->last_status = WEXITSTATUS(status);
	}
	return (1);
}

int	builtin_heredoc(t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		data->last_status = 1;
		return (0);
	}
	if (pid == 0)
		run_heredoc_child(data);
	else
	{
		return (wait_and_handle_heredoc(data, pid));
	}
	return (1);
}
