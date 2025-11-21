/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:57:07 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/21 20:52:58 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirect_av_enter(void)
{
	struct stat	st;

	if (fstat(STDIN_FILENO, &st) == -1)
		return (perror("fstat"), 1);
	if (S_ISFIFO(st.st_mode) || S_ISREG(st.st_mode))
		return (printf("Erreur  pipe ou une redirection.\n"), 1);
	return (0);
}

int	ac_av_malloc_data(int ac, char **av, t_data **data)
{
	(void)av;
	(void)ac;
	*data = malloc(sizeof(**data));
	if (!*data)
		return (0);
	return (1);
}

void	execute_and_clean(t_data *data)
{
	exe(data);
	free(data->input_clean);
	data->input_clean = NULL;
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_data	*data;

	if (redirect_av_enter())
		return (1);
	if (!ac_av_malloc_data(ac, av, &data))
		return (1);
	init_data(data, envp);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			ft_putstr_fd("exit", 1);
			write(1, "\n", 1);
			minishell_clean_exit(data, data->last_status);
		}
		if (*input)
			add_history(input);
		if (ft_parsing(input, data))
			execute_and_clean(data);
		free(input);
	}
	free_all(data);
	return (0);
}
