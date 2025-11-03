

#include "../../includes/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
}

void	free_tab3(char ***tab3)
{
	int	i;

	if (!tab3)
		return ;
	i = 0;
	while (tab3[i])
	{
		free_tab(tab3[i]);
		tab3[i] = NULL;
		i++;
	}
	free(tab3);
}

void	free_fd_array(int **fds)
{
	int	i;

	if (!fds)
		return ;
	i = 0;
	while (fds[i])
	{
		free(fds[i]);
		fds[i] = NULL;
		i++;
	}
	free(fds);
}

void	free_all(t_data *data)
{
	if (!data)
		return ;
	if (data->input_clean)
	{
		free(data->input_clean);
		data->input_clean = NULL;
	}
	if (data->limiter)
	{
		free_tab(data->limiter);
		data->limiter = NULL;
	}
	if (data->argv)
	{
		free_tab(data->argv);
		data->argv = NULL;
	}
	if (data->argv_clean_quotes)
	{
		free_tab(data->argv_clean_quotes);
		data->argv_clean_quotes = NULL;
	}
	if (data->argv_only_cmd)
	{
		free_tab(data->argv_only_cmd);
		data->argv_only_cmd = NULL;
	}
	if (data->here_doc_argv)
	{
		free_tab(data->here_doc_argv);
		data->here_doc_argv = NULL;
	}
	if (data->argv_pipeline)
	{
		free_tab3(data->argv_pipeline);
		data->argv_pipeline = NULL;
	}
	if (data->echo_pipline)
	{
		free_tab3(data->echo_pipline);
		data->echo_pipline = NULL;
	}

	if (data->pipeline_in_fds)
	{
		free_fd_array(data->pipeline_in_fds);
		data->pipeline_in_fds = NULL;
	}
	if (data->pipeline_out_fds)
	{
		free_fd_array(data->pipeline_out_fds);
		data->pipeline_out_fds = NULL;
	}

	if (data->infile_fd > 2)
	{
		close(data->infile_fd);
		data->infile_fd = -1;
	}
	if (data->outfile_fd > 2)
	{
		close(data->outfile_fd);
		data->outfile_fd = -1;
	}
	if (data->error_fd > 2)
	{
		close(data->error_fd);
		data->error_fd = -1;
	}
}
