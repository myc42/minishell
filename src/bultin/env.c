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
/*   Created: 2025/11/04 18:26:39 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/04 18:26:39 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


char	**copy_envp(char **envp)

{
	int count;
	int i;
	char **copy;

	count = 0;
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

int	builtin_env(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
		{
			ft_putstr_fd(envp[i], 1);
			write(1, "\n", 1);
		}
		i++;
	}
	return (0);
}

void	update_or_add_var(char *arg, char ***envp)
{
	size_t len;
	int idx;
	char *name;
	char *eq;

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

int	builtin_export(char **argv, char ***envp)
{
	int i;
	int ret;

	if (!argv[1])
		return (builtin_env(*envp));
	i = 1;
	ret = 0;
	while (argv[i])
	{
		/*if (!ft_strchr(argv[i], '=') || !is_valid_identifier(argv[i]))
		{
			ft_putstr_fd("minishell: export: invalid format: ", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("\n", 2);
			ret = 1;
		}
		else*/
		update_or_add_var(argv[i], envp);
		i++;
	}
	return (ret);
}

int	builtin_unset(char **argv, char ***envp)
{
	int i;
	int j;
	size_t len;

	if (!argv[1])
		return (1);
	i = 0;
	j = 0;
	while ((*envp)[i])
	{
		len = ft_strlen(argv[1]);
		if (ft_strncmp((*envp)[i], argv[1], len) == 0
			&& (*envp)[i][len] == '=')
			free((*envp)[i]);
		else
			(*envp)[j++] = (*envp)[i];
		i++;
	}
	(*envp)[j] = NULL;
	return (0);
}
