/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/10/14 17:37:30 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/14 17:37:30 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


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
