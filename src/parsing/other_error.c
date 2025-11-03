

#include "../../includes/minishell.h"

int	is_separator(char *str)
{
	return (!ft_strcmp(str, ">") || !ft_strcmp(str, ">>") || !ft_strcmp(str,
			"<") || !ft_strcmp(str, "|"));
}

int	check_after_redirection(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (is_separator(av[i]))
		{
			if (av[i + 1] == NULL || is_separator(av[i + 1]))
				return (1);
		}
		i++;
	}
	return (0);
}

int	direction_error(char *str, t_data *data)
{
	int	i;
	int	j;

	i = ft_strlen(str) - 1;
	j = 0;
	(void)data;
	while (i >= 0 && (str[i] == ' ' || str[i] == '\t'))
		i--;
	if (i >= 0 && (str[i] == '|' || str[i] == '>' || str[i] == '<'))
	{
		ft_putstr_fd("minishell$ syntax error near unexpected token `newline`\n",
			1);
		return (1);
	}
	return (0);
}

int	check_if_is_only_space(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}
