/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:45:31 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/23 18:47:55 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_parsing(char *str, t_data *data)
{
	int		quote;
	char	*expansion_str;

	quote = closed_quotes(str);
	if (!quote)
		return (ft_putstr_fd("parse error near '\n", 2), 0);
	if (direction_error(str, data) || *str == 0)
		return (ft_putstr_fd("parse error near '\n", 2), 0);
	expansion_str = expand_variables_in_string(str, data);
	data->input_clean = ft_strdup(clean_space(expansion_str));
	if (!data->input_clean)
		return (0);
	return (1);
}
