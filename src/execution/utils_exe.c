/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 19:56:07 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/05 19:42:00 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	first_argv_two(int siz, t_data *data, char **av)
{
	int	i;

	i = 0;
	data->argv = malloc(sizeof(char *) * (siz + 1));
	if (!data->argv)
		return (free_tab(av));
	i = 0;
	while (av[i])
	{
		data->argv[i] = ft_strdup(av[i]);
		i++;
	}
	data->argv[i] = NULL;
}

void	first_argv_in_tab(t_data *data, char *input, char **env)
{
	char	**av;
	char	*expan;
	char	*mult_space;
	int		size;

	(void)env;
	mult_space = clean_space(input);
	expan = expand_variables_in_string(mult_space, data);
	av = argv_valid_tab(expan);
	free(mult_space);
	free(expan);
	if (!av)
		return ;
	size = 0;
	while (av[size])
		size++;
	first_argv_two(size, data, av);
	free_tab(av);
}
