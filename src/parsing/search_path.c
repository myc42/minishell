/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:19:10 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/16 19:41:26 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_split(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**get_all_paths(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strnstr(env[i], "PATH", 4) != NULL)
			return (ft_split(env[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

char	*find_path(char **env, char *cmd)
{
	char	**paths;
	char	*path_find;
	char	*good_path;
	int		i;

	paths = get_all_paths(env);
	if (paths == NULL)
		return (NULL);
	i = 0;
	while (paths[i] != NULL)
	{
		path_find = ft_strjoin(paths[i], "/");
		if (path_find == NULL)
			return (free_split(paths), NULL);
		good_path = ft_strjoin(path_find, cmd);
		free(path_find);
		if (good_path == NULL)
			return (free_split(paths), NULL);
		if (access(good_path, F_OK | X_OK) == 0)
			return (free_split(paths), good_path);
		free(good_path);
		i++;
	}
	return (free_split(paths), NULL);
}

void	init_expans_var(char **temp, int *i, int *in_single_quotes,
		char **result)
{
	*temp = NULL;
	*i = 0;
	*in_single_quotes = 0;
	*result = malloc(500000000);
	if (!*result)
		return ;
}
