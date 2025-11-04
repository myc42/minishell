/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 23:11:04 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/04 23:11:05 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../includes/minishell.h"

int	ft_parsing(char *str, t_data *data)
{
	char	*expansion_str;
	char	*cleaned;
	char *here_doc_management;

	if (!closed_quotes(str))
		return (ft_putstr_fd("parse error near '\n", 2), 0);
	if (direction_error(str, data) || *str == 0)
		return (0);
	if (check_if_is_only_space(str))
		return (0);
	here_doc_management = separe_here_doc_sign(str);
	if (!here_doc_management)
		return (0);
	expansion_str = expand_variables_in_string(here_doc_management, data);
	free(here_doc_management);
	if (!expansion_str)
		return (0);

	cleaned = clean_space(expansion_str);
	free(expansion_str);
	if (!cleaned)
		return (0);

	data->input_clean = cleaned;
	return (1);
}
