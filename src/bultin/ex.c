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
/*   Created: 2025/11/04 18:26:51 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/04 18:26:51 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


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
