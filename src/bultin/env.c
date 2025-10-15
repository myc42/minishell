/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/10/14 18:24:49 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/14 18:24:49 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int	builtin_env(t_data *data, char **envp)
{
	while (envp[data->len_env])
	{
		if (ft_strchr(envp[data->len_env], '='))
		{
			ft_putstr_fd(envp[data->len_env], 1);
			write(1, "\n", 1);
		}
		data->len_env++;
	}
	return (0);
}

void	update_or_add_var(char *arg, char ***envp)
{
	char *eq;
	size_t len;
	char *name;
	int idx;

	eq = ft_strchr(arg, '=');
	if (!eq)
		return ;
	len = eq - arg;
	name = ft_substr(arg, 0, len);
	if (!name)
		return ;
	idx = env_var_index(*envp, name);
	free(name);
	if (idx >= 0)
	{
		free((*envp)[idx]);
		(*envp)[idx] = ft_strdup(arg);
	}
	else
		*envp = realloc_env(*envp, arg);
}

int	builtin_export(t_data *data, char ***envp)
{
	int i;

	if (!data->argv[1])
		return (builtin_env(data, *envp));
	i = 1;
	while (data->argv[i])
	{
		if (!ft_strchr(data->argv[i], '=')
			|| !is_valid_identifier(data->argv[i]))
		{
			ft_putstr_fd("minishell: export: invalid format: ", 2);
			ft_putstr_fd(data->argv[i], 2);
		}
		else
			update_or_add_var(data->argv[i], envp);
		i++;
	}
	return (0);
}

int	builtin_unset(char **argv, char ***envp)
{
	int i;
	int j;
	size_t len;
	char *efe;
	efe =malloc(100);

	if (!argv[1])
		return (1);
	i = 0;
	j = 0;
	printf(":edfeffefe") ;
	while ((*envp[i]))
	{
		len = ft_strlen(argv[1]);
		if (ft_strncmp((*envp)[i], argv[1], len) == 0
			&& (*envp)[i][len] == '=')
			free(efe);
		else
			(*envp)[j++] = (*envp)[i];
		i++;
	}
	(*envp)[j] = NULL;
	return (0);
}