

#include "../../includes/minishell.h"

int	pipe_after_limiter(t_data *data)
{
	int i;

	i = 0;
	while (data->argv[i])
	{
		if (ft_strncmp(data->argv[i], "<<", 3) == 0)
		{
			if (data->argv[i + 2] && ft_strncmp(data->argv[i + 2], "|", 2) == 0)
				return (1);
		}
		i++;
	}
	return (0);
}