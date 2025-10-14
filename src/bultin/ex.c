/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/10/14 17:37:51 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/14 17:37:51 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


char	*get_env_value(char **envp, char *name)
{
	int i;
	size_t len;

	if (!envp || !name)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, len) && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

int	has_slash(const char *s)
{
	int i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	is_executable_file(char *path)
{
	struct stat st;

	if (!path)
		return (0);
	if (stat(path, &st) == -1)
		return (0);
	if ((st.st_mode & S_IFMT) == S_IFDIR)
		return (0);
	if (access(path, X_OK) == 0)
		return (1);
	return (0);
}

static char	*path_join_cmd(char *dir, char *cmd)
{
	size_t len;
	char *tmp;
	char *full;

	if (!dir || !cmd)
		return (NULL);
	len = ft_strlen(dir);
	if (len > 0 && dir[len - 1] == '/')
	{
		full = ft_strjoin_kamel(dir, cmd);
		return (full);
	}
	tmp = ft_strjoin_kamel(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin_kamel(tmp, cmd);
	free(tmp);
	return (full);
}

char	*search_in_path(char **paths, char *cmd)
{
	char *full;
	int i;

	i = 0;
	while (paths[i])
	{
		if (*(paths[i]) != '\0')
			full = path_join_cmd(paths[i], cmd);
		else
			full = ft_strdup(cmd);
		if (full && is_executable_file(full))
		{
			ft_free_split(paths);
			return (full);
		}
		if (full)
			free(full);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

char	*find_command_path(char *cmd, t_data *shell)
{
	char *path_env;
	char **paths;

	if (!cmd || !*cmd)
		return (NULL);

	if (has_slash(cmd))
	{
		if (is_executable_file(cmd))
			return (ft_strdup(cmd));
		return (NULL);
	}

	path_env = get_env_value(shell->envp, "PATH");
	if (!path_env || !*path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	return (search_in_path(paths, cmd));
}

void	print_cmd_error(char *cmd, int has_slash)
{
	if (has_slash)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
}

int	handle_builtin(t_data *data)
{
	int status;

	status = execute_builtin(data);
	if (status != -1)
	{
		data->last_status = status;
		ft_free_split((char **)data->argv);
		return (1);
	}
	return (0);
}

char	*resolve_command(char *cmd, t_data *shell)
{
	char *cmd_path;

	cmd_path = find_command_path(cmd, shell);
	if (!cmd_path)
	{
		print_cmd_error(cmd, has_slash(cmd));
		shell->last_status = 127;
		return (NULL);
	}
	return (cmd_path);
}

void	update_status_from_signal(int st, t_data *data)
{
	int sig;

	if (WIFSIGNALED(st))
	{
		sig = WTERMSIG(st);
		if (sig == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", 2);
		else if (sig == SIGINT)
			ft_putstr_fd("\n", 1);
		data->last_status = 128 + sig;
	}
	else
		data->last_status = WEXITSTATUS(st);
}

void	exec_child_process(char *cmd, char **argv, t_data *shell)
{
	reset_signals_child();
	execve(cmd, argv, shell->envp);
	perror("execve");
	exit(126);
}


void	execute_command(char *input, t_data *shell)
{
	char **argv;
	char *cmd;
	pid_t pid;
	int st;

	if (!input)
		return ;
	argv = ft_split(input, ' ');
	if (!argv || !argv[0] || argv[0][0] == '\0')
		return (ft_free_split(argv));
	if (handle_builtin(shell))
		return ;
	cmd = resolve_command(argv[0], shell);
	if (!cmd)
		return (ft_free_split(argv));
	pid = fork();
	if (pid == 0)
		exec_child_process(cmd, argv, shell);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &st, 0);
	setup_signals();
	update_status_from_signal(st, shell);
	free(cmd);
	ft_free_split(argv);
}
