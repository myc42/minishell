/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   biltin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/11/04 18:26:03 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/04 18:26:03 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	c_pipe(t_data *data)
{
	int	i;

	i = 0;
	while (data->argv[i])
	{
		if (ft_strcmp(data->argv[i], "|") == 0
			|| is_redirection_operator(data->argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_cd(t_data *data, char **envp)
{
	if (!data->argv[1])
	{
		ft_putstr_fd("minishell: cd: missing argument\n", 2);
		return (1);
	}
	if (data->argv[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (chdir(data->argv[1]) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(data->argv[1], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	update_pwd(envp);
	return (0);
}

int	execute_builtin(t_data *data)
{
	int	i;

	i = 0;
	if (ft_strncmp(data->argv[0], "pwd", 4) == 0 && c_pipe(data))
		return (builtin_pwd());
	if (ft_strncmp(data->argv[0], "echo", 5) == 0)
		return (bult_echo(data));
	if (ft_strncmp(data->argv[0], "cd", 3) == 0 && c_pipe(data))
		return (builtin_cd(data, data->envp));
	if (ft_strncmp(data->argv[0], "env", 4) == 0)
		return (builtin_env(data->envp));
	if (ft_strncmp(data->argv[0], "export", 7) == 0)
		return (builtin_export(data->argv, &data->envp));
	if (ft_strncmp(data->argv[0], "unset", 6) == 0)
		return (builtin_unset(data->argv, &data->envp));
	if (ft_strncmp(data->argv[0], "exit", 5) == 0)
		return (builtin_exit(data));
	while (data->argv[i])
	{
		if (ft_strncmp(data->argv[i], "<<", 3) == 0)
			return (builtin_heredoc(data));
		i++;
	}
	return (-1);
}
