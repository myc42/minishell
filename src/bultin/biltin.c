/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   biltin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: knehal <knehal@student.42.fr>              +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/11/16 23:43:54 by knehal            #+#    #+#             */
/*   Updated: 2025/11/16 23:43:54 by knehal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	c_pipe(t_data *data)
{
	int	i;

	i = 0;
	if (!data->argv)
		return (1);
	while (data->argv[i])
	{
		if (!ft_strcmp(data->argv[i], "|")
			|| is_redirection_operator2(data->argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int	c_pipe2(t_data *data)
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

char	*get_env_value2(char **envp, const char *name)
{
	int		i;
	size_t	len;

	if (!envp || !name)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, len) && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

int	builtin_cd(t_data *data, char **envp)
{
	char	*target;

	if (data->argv[1] && data->argv[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (!data->argv[1])
	{
		target = get_env_value2(envp, "HOME");
		if (!target || !*target)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
	}
	else
		target = data->argv[1];
	if (chdir(target) != 0)
	{
		print_cd_error(target);
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
	if (ft_strncmp(data->argv[0], "echo", 5) == 0 && c_pipe(data))
		return (builtin_echo(data->argv, data));
	if (ft_strncmp(data->argv[0], "cd", 3) == 0 && c_pipe(data))
		return (builtin_cd(data, data->envp));
	if (ft_strncmp(data->argv[0], "env", 4) == 0 && c_pipe(data))
		return (builtin_env(data->envp));
	if (ft_strncmp(data->argv[0], "export", 7) == 0 && c_pipe(data))
		return (builtin_export(data->argv, &data->envp));
	if (ft_strncmp(data->argv[0], "unset", 6) == 0 && c_pipe(data))
		return (builtin_unset(data->argv, &data->envp));
	if (ft_strncmp(data->argv[0], "exit", 5) == 0 && c_pipe(data))
		return (builtin_exit(data));
	while (data->argv[i])
	{
		if (ft_strncmp(data->argv[i], "<<", 3) == 0)
			return (builtin_heredoc(data));
		i++;
	}
	return (-1);
}
