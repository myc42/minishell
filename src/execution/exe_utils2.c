

#include "../../includes/minishell.h"


void	init_var_exe(int *i, int *prev_pipe_read_fd, t_data *data, char *input,
		char **env)
{
	*i = 0;
	*prev_pipe_read_fd = -1;
	first_argv_in_tab(data, input, env);
}

void	update_cmd_pipenbr(t_data *data, int *pipeline_nb)
{
	redirect_and_cmds(data);
	*pipeline_nb = count_pipeline(data) + 1;
}