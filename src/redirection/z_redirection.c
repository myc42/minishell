
#include "../../includes/minishell.h"

int	fd_and_cmd_tab(t_data *data)
{
	data->infile_fd = -1;
	data->outfile_fd = -1;
	data->error_fd = -1;
	data->pipeline_in_fds = NULL;
	data->pipeline_out_fds = NULL;
	if (!redirect_and_cmds(data))
		return (0);
	return (1);
}
