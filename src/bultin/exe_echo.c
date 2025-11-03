

#include "../../includes/minishell.h"

int	ft_count_cmds_pipeline(t_data *data)
{
	int	count;

	count = 0;
	if (!data || !data->argv_pipeline)
		return (0);
	while (data->argv_pipeline[count] != NULL)
		count++;
	return (count);
}

void	remove_two_tokens(char **argv, int i)
{
	int	j;

	free(argv[i]);
	free(argv[i + 1]);
	j = i;
	while (argv[j + 2])
	{
		argv[j] = argv[j + 2];
		j++;
	}
	argv[j] = NULL;
	argv[j + 1] = NULL;
}

void	analyze_redirections(char **argv, int *in_fd, int *out_fd)
{
	int	i;

	i = 0;
	*in_fd = STDIN_FILENO;
	*out_fd = STDOUT_FILENO;
	while (argv[i])
	{
		if (strcmp(argv[i], "<") == 0 && argv[i + 1])
		{
			*in_fd = open(argv[i + 1], O_RDONLY);
			if (*in_fd < 0)
			{
				perror(argv[i + 1]);
				exit(1);
			}
			remove_two_tokens(argv, i);
		}
		else if (strcmp(argv[i], ">") == 0 && argv[i + 1])
		{
			*out_fd = open(argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			remove_two_tokens(argv, i);
		}
		else if (strcmp(argv[i], ">>") == 0 && argv[i + 1])
		{
			*out_fd = open(argv[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			remove_two_tokens(argv, i);
		}
		else
			i++;
	}
}

void	setup_redirections(t_data *data)
{
	int	cmd_count;
	int	i;

	if (!data || !data->argv_pipeline)
		return ;
	cmd_count = ft_count_cmds_pipeline(data);
	data->pipeline_in_fds = malloc(sizeof(int *) * (cmd_count + 1));
	data->pipeline_out_fds = malloc(sizeof(int *) * (cmd_count + 1));
	if (!data->pipeline_in_fds || !data->pipeline_out_fds)
		return ;
	i = 0;
	while (i < cmd_count)
	{
		data->pipeline_in_fds[i] = malloc(sizeof(int));
		data->pipeline_out_fds[i] = malloc(sizeof(int));
		if (!data->pipeline_in_fds[i] || !data->pipeline_out_fds[i])
			return ;
		analyze_redirections(
			data->argv_pipeline[i],
			data->pipeline_in_fds[i],
			data->pipeline_out_fds[i]);
		i++;
	}
	data->pipeline_in_fds[cmd_count] = NULL;
	data->pipeline_out_fds[cmd_count] = NULL;
}

void	free_pipeline_fds(t_data *data)
{
	int	i;

	if (data->pipeline_in_fds)
	{
		i = 0;
		while (data->pipeline_in_fds[i])
		{
			if (*(data->pipeline_in_fds[i]) != STDIN_FILENO)
				close(*(data->pipeline_in_fds[i]));
			free(data->pipeline_in_fds[i]);
			i++;
		}
		free(data->pipeline_in_fds);
		data->pipeline_in_fds = NULL;
	}
	if (data->pipeline_out_fds)
	{
		i = 0;
		while (data->pipeline_out_fds[i])
		{
			if (*(data->pipeline_out_fds[i]) != STDOUT_FILENO)
				close(*(data->pipeline_out_fds[i]));
			free(data->pipeline_out_fds[i]);
			i++;
		}
		free(data->pipeline_out_fds);
		data->pipeline_out_fds = NULL;
	}
}

void	free_argv_pipeline(t_data *data)
{
	int	i;
	int	j;

	if (!data || !data->argv_pipeline)
		return ;
	i = 0;
	while (data->argv_pipeline[i])
	{
		j = 0;
		while (data->argv_pipeline[i][j])
		{
			free(data->argv_pipeline[i][j]);
			j++;
		}
		free(data->argv_pipeline[i]);
		i++;
	}
	free(data->argv_pipeline);
	data->argv_pipeline = NULL;
}

void	pid_zero_one(t_data *data, int i, int prev_fd, int cmd_count,
		int *pipefd)
{
	if (*(data->pipeline_in_fds[i]) != STDIN_FILENO)
		dup2(*(data->pipeline_in_fds[i]), STDIN_FILENO);
	else if (prev_fd != -1)
		dup2(prev_fd, STDIN_FILENO);
	if (*(data->pipeline_out_fds[i]) != STDOUT_FILENO)
		dup2(*(data->pipeline_out_fds[i]), STDOUT_FILENO);
	else if (i < cmd_count - 1)
		dup2(pipefd[1], STDOUT_FILENO);
	if (prev_fd != -1)
		close(prev_fd);
	if (i < cmd_count - 1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

void	execute_pipeline(t_data *data)
{
	int		cmd_count;
	int		prev_fd;
	pid_t	pid;
	int		pipefd[2] = {-1, -1};
	int		i;

	cmd_count = ft_count_cmds_pipeline(data);
	prev_fd = -1;
	i = 0;
	while (i < cmd_count)
	{
		if (i < cmd_count - 1 && pipe(pipefd) == -1)
		{
			perror("pipe");
			exit(1);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(1);
		}
		if (pid == 0)
		{
			pid_zero_one(data, i, prev_fd, cmd_count, pipefd);
			exe_cmd(data, &i, data->envp);
			perror("execvp");
			exit(1);
		}
		if (prev_fd != -1)
			close(prev_fd);
		if (i < cmd_count - 1)
			close(pipefd[1]);
		prev_fd = (i < cmd_count - 1) ? pipefd[0] : -1;
		i++;
	}
	i = 0;
	while (i++ < cmd_count)
		wait(NULL);
}

int	exe_echox(t_data *data)
{
	cpy_clean_quotes_to_av(data);
	ft_split_by_pipe(data);
	setup_redirections(data);
	execute_pipeline(data);
	free_pipeline_fds(data);
	free_argv_pipeline(data);
	return (1);
}
