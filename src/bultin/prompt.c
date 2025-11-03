

#include "../../includes/minishell.h"


void	ft_free_split(char **tab)
{
	int i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}