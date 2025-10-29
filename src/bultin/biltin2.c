/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   biltin2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:00:16 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/29 02:27:28 by macoulib         ###   ########.fr       */
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

	new_pwd = ft_strjoin_kamel(prefix, cwd);
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

void	print_arg(char *arg, t_data *data)
{
	char *code;

	if (ft_strncmp(arg, "$?", 3) == 0)
	{
		code = ft_itoa(data->last_status);
		ft_putstr_fd(code, 1);
		free(code);
	}
	else
		ft_putstr_fd(arg, 1);
}

int	is_n(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (i > 1);
}


int	builtin_echo(char **argv, t_data *data)
{
	int i;
	int newline;

	i = 1;
	newline = 1;

	while (argv[i] && is_n(argv[i]))
	{
		newline = 0;
		i++;
	}
	while (argv[i])
	{
		print_arg(argv[i], data);
		if (argv[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", 1);
	return (0);
}