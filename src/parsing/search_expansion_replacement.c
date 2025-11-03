#include "../../includes/minishell.h"

int	ft_strncmps(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!s1 || !s2)
		return (1);
	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	*search_expansion_replacement(char *var_name, t_data *data)
{
	char	*value;
	int		i;

	if (!var_name || !data || !data->envp)
		return (ft_strdup("")); 

	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(data->last_status));

	value = NULL;
	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmps(data->envp[i], var_name, ft_strlen(var_name)) == 0
			&& data->envp[i][ft_strlen(var_name)] == '=')
		{
			free(value);
			value = ft_strdup(data->envp[i] + ft_strlen(var_name) + 1);
			break;
		}
		i++;
	}

	if (!value)
		value = ft_strdup("");
	return (value);
}
