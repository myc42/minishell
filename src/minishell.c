/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:25:46 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/05 18:38:56 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_pipeline_tab(char ***pipelines)
{
	int	i;

	if (!pipelines)
		return ;
	i = 0;
	while (pipelines[i])
	{
		free_tab(pipelines[i]);
		i++;
	}
	free(pipelines);
}

void	free_parsing(t_data *d)
{
	if (d->input_clean)
		free(d->input_clean);
	d->input_clean = NULL;
	free_tab(d->argv);
	free_tab(d->argv_clean_quotes);
	free_tab(d->argv_only_cmd);
	free_tab(d->here_doc_argv);
	free_pipeline_tab(d->argv_pipeline);
	free_tab(d->limiter);
	d->argv = NULL;
	d->argv_clean_quotes = NULL;
	d->argv_only_cmd = NULL;
	d->here_doc_argv = NULL;
	d->argv_pipeline = NULL;
	d->limiter = NULL;
}

int	first_funct(char **av, int ac, t_data **data, char **envp)
{
	struct stat	st;

	if (fstat(STDIN_FILENO, &st) == -1)
		return (perror("fstat"), 1);
	if (S_ISFIFO(st.st_mode) || S_ISREG(st.st_mode))
		return (fprintf(stderr, "Erreur : pipe ou redirection détectée.\n"), 1);
	(void)av;
	(void)ac;
	*data = malloc(sizeof(**data));
	if (!*data)
		return (1);
	init_data(*data, envp);
	return (0);
}

void	last_funct(t_data *data)
{
	if (data->envp)
		free_tab(data->envp);
	free(data);
	rl_clear_history();
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_data	*data;

	if (first_funct(av, ac, &data, envp))
		return (1);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			ft_putstr_fd("exit\n", 1);
			free_parsing(data);
			break ;
		}
		if (*input)
			add_history(input);
		if (ft_parsing(input, data))
			exe(data, data->input_clean, data->envp);
		free_parsing(data);
		free(input);
		start_data(data);
	}
	if (data)
		last_funct(data);
	return (0);
}
