/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_expansion_replacement.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:22:10 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/14 21:05:59 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strncmps(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s1cpy;
	unsigned char	*s2cpy;
	size_t			i;

	i = 0;
	s1cpy = (unsigned char *)s1;
	s2cpy = (unsigned char *)s2;
	while (i != n && (s1cpy[i] != '\0' || s2cpy[i] != '\0'))
	{
		if (s1cpy[i] != s2cpy[i])
			return (s1cpy[i] - s2cpy[i]);
		i++;
	}
	return (0);
}

char	*search_expansion_replacement(char *var_name, t_data *data)
{
	int		i;
	size_t	len;

	if (!var_name || !data || !data->envp)
		return (NULL);
	if (!ft_strcmp(var_name, "?"))
		return (ft_itoa(data->last_status));
	len = ft_strlen(var_name);
	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmps(data->envp[i], var_name, len) == 0
			&& data->envp[i][len] == '=')
			return (ft_strdup(data->envp[i] + len + 1));
		i++;
	}
	return (NULL);
}
