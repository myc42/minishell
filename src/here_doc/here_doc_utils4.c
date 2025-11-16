/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:32:21 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/14 21:00:45 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	int_var_stock(int *current, int *total, t_data *data)
{
	int	x;

	*total = 0;
	x = 0;
	while (data->limiter && data->limiter[x])
		x++;
	*total = x;
	*current = 0;
}

int	check_nbr_limiter(t_data *data)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (data->argv[i])
	{
		if (ft_strncmp(data->argv[i], "<<", 3) == 0 && data->argv[i + 1])
			count++;
		i++;
	}
	return (count);
}

void	find_all_limiters(t_data *data)
{
	int	count;
	int	i;
	int	j;

	count = check_nbr_limiter(data);
	data->limiter = malloc(sizeof(char *) * (count + 1));
	if (!data->limiter)
		return ;
	i = 0;
	j = 0;
	while (data->argv[i])
	{
		if (ft_strncmp(data->argv[i], "<<", 3) == 0 && data->argv[i + 1])
		{
			data->limiter[j++] = ft_strdup(data->argv[i + 1]);
		}
		i++;
	}
	data->limiter[j] = NULL;
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
	{
		run_heredoc_child(data);
		exit(1);
	}
	return (wait_and_handle_heredoc(data, pid));
}
