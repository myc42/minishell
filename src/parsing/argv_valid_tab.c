/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_valid_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:00:21 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/28 03:46:41 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	three_variable_init(int *i, int *j, int *k)
{
	*i = 0;
	*j = 0;
	*k = 0;
}
int	get_word_len(char *str, int *start_index)
{
	int	len;
	int	i;
	int	in_s;
	int	in_d;

	len = 0;
	i = *start_index;
	in_s = 0;
	in_d = 0;
	while (str[i] == ' ')
		i++;
	*start_index = i;
	while (str[i])
	{
		if (str[i] == '\'' && !in_d)
			in_s = !in_s;
		else if (str[i] == '\"' && !in_s)
			in_d = !in_d;
		else if (str[i] == ' ' && !in_s && !in_d)
			break ;
		len++;
		i++;
	}
	return (len);
}

char	*copy_word(char *str, int start, int len)
{
	char	*word;
	int		k;

	k = 0;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while (k < len)
	{
		word[k] = str[start + k];
		k++;
	}
	word[len] = '\0';
	return (word);
}

char	**argv_valid_tab(char *str)
{
	char	**argv_tab;
	int		j;
	int		i;
	int		len;

	three_variable_init(&i, &j, &len);
	argv_tab = malloc(sizeof(char *) * (count_argv(str) + 1));
	if (!argv_tab)
		return (NULL);
	while (str[i])
	{
		len = get_word_len(str, &i);
		if (len > 0)
		{
			argv_tab[j] = copy_word(str, i, len);
			if (!argv_tab[j])
				return (NULL);
			j++;
			i += len;
		}
		else
			break ;
	}
	argv_tab[j] = NULL;
	return (argv_tab);
}
