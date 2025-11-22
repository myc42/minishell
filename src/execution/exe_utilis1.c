/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utilis1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 15:29:48 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/22 21:11:26 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_eacces_or_isdir(char *cmd_path)
{
	if (cmd_path)
		free(cmd_path);
	exit(126);
}

int	is_operator(char *token)
{
	return (strcmp(token, "|") == 0 || strcmp(token, "<") == 0 || strcmp(token,
			">") == 0 || strcmp(token, ">>") == 0);
}

int	detect_bad_input(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (is_operator(argv[i]))
		{
			if (!argv[i + 1] || is_operator(argv[i + 1]))
			{
				if (argv[i + 1])
				{
					printf("minishell: syntax error near");
					printf(" unexpected token `%s'\n", argv[i + 1]);
				}
				else
				{
					printf("minishell: syntax error near");
					printf(" unexpected token `\\n'\n");
				}
				return (0);
			}
		}
		i++;
	}
	return (1);
}
