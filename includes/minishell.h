/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 19:02:12 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/18 00:13:05 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../librairie/ft_libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_data
{
	char						**envp;
	char						**argv;
	char						**argv_only_cmd;
	char						***argv_pipeline;
	char						*limiter;
	int							infile_fd;
	int							outfile_fd;
	int							error_fd;
	int							last_status;
	int							len_env;
}								t_data;

int								ft_isspace(char c);
int								closed_quotes(char *str);
char							*expand_variables_in_string(char *str,
									char **envp);
char							*find_path(char **env, char *cmd);
char							*delete_multiple_space(char *str);
int								ft_strncmps(const char *s1, const char *s2,
									size_t n);
char							*search_expansion_replacement(char *str,
									char **envp);
char							*expand_variables_in_string(char *str,
									char **envp);
int								count_argv(char *str);
void							init_variable(int *argv, int *i, int *count,
									int *s, int *d);
void							is_word(int *argv, int *count, int s, int d);
char							**argv_valid_tab(char *str);
int								ft_strcmp(char *s1, char *s2);
int								ft_parsing(char *str, t_data *data);
int								creat_fd_infile(t_data *data, int *i);
int								creat_fd_outfile(t_data *data, int *i);
int								is_redirection_operator(char *av);
int								redirect_and_cmds(t_data *data, int ac,
									char **envp);
int								count_cmd_elements(t_data *data);
int								only_cmd_tab(t_data *data);
int								direction_error(char *str, t_data *data);
int								fd_and_cmd_tab(t_data *data, char **av, int ac,
									char **envp);
int								redirection_detected(char **av);
void							create_pipeline_tab(t_data *data);
void							exe(t_data *data, char *input, int ac,
									char **env);
int								count_pipeline(t_data *data);
void							pipeline_space(char *str, char *dest);
void							init_variables_to_zero(int *i, int *j, int *k,
									int *l);
char							*clean_space(char *str);
char							*get_next_line(int fd);
void							alloc_without_limiter(t_data *data);

void							tab_without_limiter(t_data *data);
int								find_limiter(t_data *data);
// ---- kamel
void							ft_free_split(char **tab);
void							execute_command(char *input, t_data *shell);
char							*find_command_path(char *cmd, t_data *shell);
int								execute_builtin(t_data *data);
char							**copy_envp(char **envp);
char							*get_env_value(char **envp, char *name);
char							*search_in_path(char **paths, char *cmd);
int								handle_builtin(t_data *shell);
char							*resolve_command(char *cmd, t_data *shell);
void							update_status_from_signal(int st,
									t_data *shell);
void							exec_child_process(char *cmd, char **argv,
									t_data *shell);
int								is_numeric(char *s);
int								builtin_exit(t_data *data);
void							update_or_add_var(char *arg, char ***envp);
int								builtin_unset(char **argv, char ***envp);
void							init_data(t_data *data, char **envp);
void							start_data(t_data *shell);
void							cleanup_shell(t_data *shell);
void							handle_sigint(int sig);
void							handle_sigquit(int sig);
void							setup_signals(void);
void							reset_signals_child(void);
char							**realloc_env(char **envp, char *new_var);
int								env_var_index(char **envp, char *name);
int								is_valid_identifier(char *s);
char							*ft_strjoin_kamel(char *s1, char *s2);
int								builtin_heredoc(t_data *data);
int								builtin_env(char **envp);
int								builtin_export(char **argv, char ***envp);
void							exe_here_doc(t_data *data , int *fd );
void	exe_cmd(t_data *data, int *i, char **envp);

extern volatile sig_atomic_t	g_signal;

#endif
