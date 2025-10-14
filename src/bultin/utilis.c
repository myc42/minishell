/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/10/14 17:38:58 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/14 17:38:58 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


char	**realloc_env(char **envp, char *new_var)
{
	int i;
	char **new_env;

	i = 0;
	while (envp && envp[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (envp && envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
		i++;
	}
	new_env[i] = ft_strdup(new_var);
	new_env[i + 1] = NULL;
	if (envp)
		ft_free_split(envp);
	return (new_env);
}

int	env_var_index(char **envp, char *name)
{
	int i;
	size_t len;

	i = 0;
	len = ft_strlen(name);
	while (envp[i])
	{
		if (ft_strncmp(envp[1], name, len) == 0 && envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	is_valid_identifier(char *s)
{
	int i;

	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}