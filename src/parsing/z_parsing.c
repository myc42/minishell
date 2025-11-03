

#include "../../includes/minishell.h"

int	ft_parsing(char *str, t_data *data)
{
	char	*expansion_str;
	char	*cleaned;
	char	*cleaner_here_doc;

	if (!str)
		return (0);
	if (!closed_quotes(str))
		return (ft_putstr_fd("parse error near '\n", 2), 0);
	if (direction_error(str, data) || *str == 0)
		return (0);
	if (check_if_is_only_space(str))
		return (0);
	cleaner_here_doc = separe_here_doc_sign(str);
	if (!cleaner_here_doc)
		return (0);
	expansion_str = expand_variables_in_string(cleaner_here_doc, data);
	if (!expansion_str)
		return (0);
	free(cleaner_here_doc);
	cleaned = clean_space(expansion_str);
	free(expansion_str);
	if (!cleaned)
		return (0);
	data->input_clean = cleaned;
	return (1);
}
