

#include "../../includes/minishell.h"

void	expansion_here_doc(int fdin, int fdout, t_data *data)
{
	char c;
	char next;
	char *status_str;
	size_t status_len;
	char stockage[100];
	int i;
	char *resultstockage;

	status_str = ft_itoa(data->last_status);
	status_len = ft_strlen(status_str);
	while (read(fdin, &c, 1) > 0)
	{
		if (c == '$')
		{
			if (read(fdin, &next, 1) > 0)
			{
				if (next == '?')
				{
					write(fdout, status_str, status_len);
				}
				else
				{
					i = 0;
					stockage[i++] = next;
					while (read(fdin, &c, 1) > 0 && !isspace(c) && c != '$'
						&& c != '\n')
					{
						if (i < (int)(sizeof(stockage) - 1))
							stockage[i++] = c;
					}
					stockage[i] = '\0';
					resultstockage = search_expansion_replacement(stockage,
							data);
					if (resultstockage == NULL)
						write(fdout, stockage, strlen(stockage));
					else
						write(fdout, resultstockage, strlen(resultstockage));
					if (!isspace(c) && c != '\n' && c != '$')
						write(fdout, &c, 1);
					else if (c == '$')
					{
						lseek(fdin, -1, SEEK_CUR);
					}
					else
					{
						write(fdout, &c, 1);
					}
				}
			}
			else
			{
				write(fdout, &c, 1);
			}
		}
		else
		{
			write(fdout, &c, 1);
		}
	}
	free(status_str);
}

