/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:57:07 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/11 19:23:39 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_data	*data;

	(void)av;
	(void)ac;
	data = malloc(sizeof(*data));
	if (!data)
		return (0);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			ft_putstr_fd("exit", 1);
			write(1, "\n", 1);
			break ;
		}
		if (*input)
			add_history(input);
		//if (!ft_parsing(input, data, envp))
			//break ;
		exe(data, input, ac, envp);
	}
	return (0);
}
