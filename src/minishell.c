/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:57:07 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/25 01:02:55 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	acav_void(int ac, char **av)
{
	(void)av;
	(void)ac;
}

int	redirect_av_enter(void)
{
	struct stat	st;

	if (fstat(STDIN_FILENO, &st) == -1)
		return (perror("fstat"), 1);
	if (S_ISFIFO(st.st_mode) || S_ISREG(st.st_mode))
		return (fprintf(stderr, "Erreur  pipe ou une redirection.\n"), 1);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_data	*data;

	acav_void(ac, av);
	if (redirect_av_enter())
		return (1);
	data = malloc(sizeof(*data));
	if (!data)
		return (0);
	init_data(data, envp);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			ft_putstr_fd("exit \n", 1);
			break ;
		}
		if (*input)
			add_history(input);
		if (ft_parsing(input, data))
			exe(data, data->input_clean, (char **)data->envp);
	}
	return (0);
}
