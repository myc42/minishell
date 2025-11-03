

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
	char **paths;
	char *path_find;
	char *good_path;
	int i;

	paths = get_all_paths(env);
	if (paths == NULL)
		return (NULL);
	i = 0;
	while (paths[i] != NULL)
	{
		path_find = ft_strjoin(paths[i], "/");
		if (path_find == NULL)
			return (NULL);
		good_path = ft_strjoin(path_find, cmd);
		free(path_find);
		if (good_path == NULL)
			return (NULL);
		if (access(good_path, F_OK | X_OK) == 0)
			return (free_split(paths), good_path);
		free(good_path);
		i++;
	}
	free_split(paths);
	return (NULL);
}
