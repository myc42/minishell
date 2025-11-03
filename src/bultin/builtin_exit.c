
#include "../../includes/minishell.h"


void	minishell_clean_exit(t_data *data, int status)
{
	free_parsing(data);

	if (data->envp)
		free_tab(data->envp);

	free(data);
	rl_clear_history();
	exit(status);
}

int	is_numeric(char *s)
{
	int i;

	i = 0;
	if (!s)
		return (0);
	if (s[0] == '+' || s[0] == '-')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(t_data *data)
{
	long	code;

	ft_putstr_fd("exit\n", 1);
	if (!data->argv[1])
		minishell_clean_exit(data, data->last_status);
	if (!is_numeric(data->argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(data->argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		minishell_clean_exit(data, 2);
	}
	if (data->argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		data->last_status = 1;
		return (1);
	}
	code = (long)ft_atoi(data->argv[1]);
	minishell_clean_exit(data, (int)(code % 256));
	return (0);
}

/*int	builtin_exit(t_data *data)
{
	ft_putstr_fd("exit\n", 1);
	if (!data->argv[1])
		exit(data->last_status);
	if (!is_numeric(data->argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(data->argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);
	}
	if (data->argv[2])

	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		data->last_status = 1;
		return (1);
	}
	exit(ft_atoi(data->argv[1]) % 256);
}
*/