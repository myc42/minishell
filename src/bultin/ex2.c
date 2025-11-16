/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:27:26 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/16 23:10:37 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(char **envp, char *name)
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

int	has_slash(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	is_executable_file(char *path)
{
	struct stat	st;

	if (!path)
		return (0);
	if (stat(path, &st) == -1)
		return (0);
	if ((st.st_mode & S_IFMT) == S_IFDIR)
		return (0);
	if (access(path, X_OK) == 0)
		return (1);
	return (0);
}

char	*path_join_cmd(char *dir, char *cmd)
{
	size_t	len;
	char	*tmp;
	char	*full;

	if (!dir || !cmd)
		return (NULL);
	len = ft_strlen(dir);
	if (len > 0 && dir[len - 1] == '/')
	{
		full = ft_strjoin_kamel(dir, cmd);
		return (full);
	}
	tmp = ft_strjoin_kamel(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin_kamel(tmp, cmd);
	free(tmp);
	return (full);
}

char	*search_in_path(char **paths, char *cmd)
{
	char	*full;
	int		i;

	i = 0;
	while (paths[i])
	{
		if (*(paths[i]) != '\0')
			full = path_join_cmd(paths[i], cmd);
		else
			full = ft_strdup(cmd);
		if (full && is_executable_file(full))
		{
			ft_free_split(paths);
			return (full);
		}
		if (full)
			free(full);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}
