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
/*   Created: 2025/10/14 17:37:19 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/14 17:37:19 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


char	**copy_envp(char **envp)

{
	int count = 0;
	int i;
	char **copy;

	while (envp[count])
		count++;
	copy = malloc((count + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		copy[i] = ft_strdup(envp[i]);
		i++;
	}
	copy[count] = NULL;
	return (copy);
}

int	builtin_pwd(void)
{
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putstr_fd(cwd, 1);
		write(1, "\n", 1);
		return (0);
	}
	perror("pwd");
	return (1);
}

void	print_arg(t_data *data)
{
	char *code;

	if (ft_strncmp(data->argv[0], "$?", 3) == 0)
	{
		code = ft_itoa(data->last_status);
		ft_putstr_fd(code, 1);
		free(code);
	}
	else
		ft_putstr_fd(data->argv[0], 1);
}

void	update_pwd(char **envp)
{
	char cwd[1024];
	char *new_pwd;
	char *prefix;
	int i;
	i = 0;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return ;
	prefix = ft_strdup("PWD=");
	if (!prefix)
		return ;

	new_pwd = ft_strjoin(prefix, cwd);
	free(prefix);
	if (!new_pwd)
		return ;

	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
		{
			free(envp[i]);
			envp[i] = new_pwd;
			return ;
		}
		i++;
	}
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
	if (ft_strncmp(data->argv[0], "cd", 3) == 0)
		return (builtin_cd(data, data->envp));
	if (ft_strncmp(data->argv[0], "export", 7) == 0)
		return (builtin_export(data, &data->envp));
	if (ft_strncmp(data->argv[0], "unset", 6) == 0)
		return (builtin_unset(data, &data->envp));
	if (ft_strncmp(data->argv[0], "exit", 5) == 0)
		return (builtin_exit(data));
	return (-1);
}