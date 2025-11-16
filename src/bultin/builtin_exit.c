/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/11/16 16:05:30 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/16 16:05:30 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_pipeline_and_fd(t_data *data, int *cmd_count, int pipefd[2])
{
	*cmd_count = ft_count_cmds_pipeline(data);
	if (*cmd_count == 0)
		*cmd_count = 1;
	pipefd[0] = -1;
	pipefd[1] = -1;
}

void	free_parsing(t_data *d)
{
	if (d->input_clean)
		free(d->input_clean);
	d->input_clean = NULL;
	free_tab(d->argv);
	free_tab(d->argv_clean_quotes);
	free_tab(d->argv_only_cmd);
	free_tab(d->here_doc_argv);
	free_tab(d->limiter);
	d->argv = NULL;
	d->argv_clean_quotes = NULL;
	d->argv_only_cmd = NULL;
	d->here_doc_argv = NULL;
	d->argv_pipeline = NULL;
	d->limiter = NULL;
}

void	minishell_clean_exit(t_data *data, int status)
{
	free_parsing(data);
	if (data->envp)
		free_tab(data->envp);
	rl_clear_history();
	free_all(data);
	free_fds_and_pipelines(data);
	free(data);
	exit(status);
}

int	is_numeric(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (s[0] == '+' || s[0] == '-')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(t_data *data)
{
	long	code;

	ft_putstr_fd("exit\n", 1);
	if (!data->argv[1])
		minishell_clean_exit(data, data->last_status);
	if (!is_numeric(data->argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(data->argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		minishell_clean_exit(data, 2);
	}
	if (data->argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		data->last_status = 1;
		return (1);
	}
	code = (long)ft_atoi(data->argv[1]);
	minishell_clean_exit(data, (int)(code % 256));
	return (0);
}
