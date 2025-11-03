

#include "../../includes/minishell.h"

int	closed_quotes(char *str)
{
	int	in_single_quote;
	int	in_double_quote;
	int	i;

	in_single_quote = 0;
	in_double_quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (str[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		i++;
	}
	if (!in_single_quote && !in_double_quote)
		return (1);
	return (0);
}
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char	*separe_here_doc_sign(char *str)
{
	int		i;
	int		j;
	char	*cpystr;

	cpystr = malloc(ft_strlen(str) * 2);
	if (!cpystr)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i
				+ 1] == '<'))
		{
			cpystr[j++] = str[i++];
			cpystr[j++] = str[i++];
			if (str[i] && !ft_isspace(str[i]))
				cpystr[j++] = ' ';
			continue ;
		}
		if (str[i] == '>' || str[i] == '<')
		{
			cpystr[j++] = str[i++];
			if (str[i] && !ft_isspace(str[i]))
				cpystr[j++] = ' ';
			continue ;
		}
		cpystr[j++] = str[i++];
	}
	cpystr[j] = '\0';
	return (cpystr);
}
