/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 19:02:12 by macoulib          #+#    #+#             */
/*   Updated: 2025/11/22 21:35:53 by macoulib         ###   ########.fr       */
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

extern volatile sig_atomic_t	g_signal;

typedef struct s_data
{
	char						*temp;
	char						**envp;
	char						*input_clean;
	char						**argv;
	char						**argv_clean_quotes;
	char						**argv_only_cmd;
	char						**here_doc_argv;
	char						***argv_pipeline;
	char						**limiter;
	int							infile_fd;
	int							outfile_fd;
	int							error_fd;
	int							last_status;
	int							len_env;
	int							**pipeline_in_fds;
	int							**pipeline_out_fds;
	int							**pipeline_err_fds;
	char						***echo_pipline;

}								t_data;

void							init_pipeline_fds_to_null(t_data *data);
int								builtin_cd(t_data *data, char **envp);
void							free_argv_pipeline(t_data *data);
void							free_pipeline_fds(t_data *data);
void							free_pipeline_fd_two(t_data *data, int i);
int								ft_isspace(char c);
int								closed_quotes(char *str);
int								find_nbr_limiter(t_data *data);
char							*find_path(char **env, char *cmd);
char							*delete_multiple_space(char *str);
int								ft_strncmps(const char *s1, const char *s2,
									size_t n);
char							*search_expansion_replacement(char *str,
									t_data *data);
char							*expand_variables_in_string(char *str,
									t_data *data);
int								count_argv(char *str);
void							init_variable(int *i, int *count, int *s,
									int *d);
void							is_word(int *argv, int *count, int s, int d);
char							**argv_valid_tab(char *str);
int								ft_strcmp(char *s1, char *s2);
int								ft_parsing(char *str, t_data *data);
int								creat_fd_infile(t_data *data, int *i);
int								creat_fd_outfile(t_data *data, int *i);
int								is_redirection_operator(char *av);
int								redirect_and_cmds(t_data *data, int x);
int								count_cmd_elements(t_data *data);
int								only_cmd_tab(t_data *data);
int								direction_error(char *str, t_data *data);
int								fd_and_cmd_tab(t_data *data);
int								redirection_detected(char **av);
void							create_pipeline_tab(t_data *data);
void							exe(t_data *data);
int								count_pipeline(t_data *data);
void							pipeline_space(char *str, char *dest);
void							init_variables_to_zero(int *i, int *j, int *k,
									int *l);
char							*clean_space(char *str);
char							*get_next_line(int fd);
void							alloc_without_limiter(t_data *data);
void							tab_without_limiter(t_data *data);
void							cpy_here_doc_argv(t_data *data);
void							exe_heredoc(t_data *data, int outfile);
void							init_var_heredoc(t_data *data,
									int *prev_pipe_read_fd, int *pipeline_nb,
									int *i);
void							pipe_fd(int *fds);
char							**copy_envp(char **envp);
void							ft_waitpid(pid_t pid);
void							free_data_argv(t_data *data);
void							ft_forkpid(pid_t *pid);
void							signal_and_waitpid(t_data *data, pid_t pid);
void							pipe_fd(int *fds);
void							exe_pid_parent(int *prev_pipe_read_fd,
									int pipeline_nb, int *fds, int *i);
void							close_infile_outfile(t_data *data, pid_t pid);
void							init_var_exe(int *i, int *prev_pipe_read_fd,
									t_data *data, char *input);
void							first_argv_in_tab(t_data *data, char *input,
									char **env);
int								ft_count_cmds_pipeline(t_data *data);
void							remove_two_tokens(char **argv, int i);
int								analyze_redirections(char **argv, int *in_fd,
									int *out_fd, int *err_fd);
int								setup_redirections(t_data *data);

void							set_output_fd(int i, int pipeline_nb,
									t_data *data, int *fds);
void							set_input_fd(int prev_pipe_read_fd, int i,
									t_data *data);
void							reset_signals_child(void);
int								builtin_echo(char **argv, t_data *data);
void							expansion_here_doc(int fdin, int fdout,
									t_data *data);
void							free_all(t_data *data);
void							free_tab(char **tab);
int								pipe_after_limiter(t_data *data);
void							clean_quotes(t_data *data);
void							cpy_clean_quotes_to_av(t_data *data);
char							*remove_quotes(const char *str);
int								check_if_is_only_space(char *str);
int								check_nbr_limiter(t_data *data);
void							find_all_limiters(t_data *data);
int								exe_echox(t_data *data);
void							rearrange_grep(t_data *data);
int								search_grep(char **argv);
char							*clean_parenthese(char *str);
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
void							exe_here_doc(t_data *data, int *fd);
void							exe_cmd(t_data *data, int *i, char **envp);
char							*get_env_value(char **envp, char *name);
int								has_slash(const char *s);
int								is_executable_file(char *path);
char							*search_in_path(char **paths, char *cmd);
char							**copy_envp(char **envp);
int								builtin_pwd(void);
void							update_pwd(char **envp);
void							print_arg(char *arg, t_data *data);
int								builtin_echo(char **argv, t_data *data);
void							print_arg(char *arg, t_data *data);
void							handle_sigint_heredoc(int sig);
void							ft_split_by_pipe(t_data *data);
int								execute_builtin(t_data *data);
void							free_parsing(t_data *d);
char							*separe_here_doc_sign(char *str);
int								update_cmd_pipenbr(t_data *data,
									int *pipeline_nb);
void							execute_pipeline(t_data *data, int infile_fd);
int								exe_echox(t_data *data);

void							first_argv_in_tab(t_data *data, char *input,
									char **env);
int								check_directions_on_tab(t_data *data);
void							close_signal(t_data *data,
									int prev_pipe_read_fd, pid_t pid);
void							if_cmd_inexistant(char **argv_exec);
void							if_after_exeve(char *cmd_path);
void							free_fd_array(int **fds);
void							free_tab3(char ***tab3);
void							free_tab(char **tab);
void							ft_forkpid(pid_t *pid);
void							pid_parent_zero(int *prev_pipe_read_fd,
									int pipeline_nb, int *i, int *fds);
void							if_pid_zero_two(t_data *data, int i,
									int pipeline_nb, int *fds);
void							if_pid_zero_one(int prev_pipe_read_fd, int i,
									int outfile);
void							three_variable_init(int *i, int *j, int *k);
void							quotes_and_increment(int *in_single_quotes,
									int *i);
void							free_s1s2(int free_s1, int free_s2, char *s1,
									char *s2);
char							*expand_variables_in_string(char *str,
									t_data *data);
char							*append_variable(char *str, int *i,
									char *result, t_data *data);
char							*append_dollar_literal(char *result);
char							*append_char(char *result, char c);
char							*ft_strjoin_free(char *s1, char *s2,
									int free_s1, int free_s2);
void							free_utils2(t_data *data);
void							free_utils3(t_data *data);
void							int_var_stock(int *current, int *total,
									t_data *data);
void							write_outfiled(int current, int total,
									int outfilefd, char *line);
void							find_cpy_redirect(t_data *data);
int								stock_to_here_doc(t_data *data, int outfilefd);
void							execute_pipelines(t_data *data, int i,
									int prev_pipe_read_fd, int pipeline_nb);
int								check_redirect_slash(t_data *data);
void							minishell_clean_exit(t_data *data, int status);
void							update_argv_here_doc(t_data *data);
char							*normalize_quotes(char *input);
void							print_cmd_error(char *cmd, int has_slash);
void							set_echoctl(int on);
void							init_pipeline_and_fd(t_data *data,
									int *cmd_count, int pipefd[2]);
int								ft_count_cmds_pipeline(t_data *data);
void							remove_two_tokens(char **argv, int i);
void							signal_and_waitpid(t_data *data, pid_t pid);
void							update_argv_in_tab(t_data *data);
void							close_signal(t_data *data,
									int prev_pipe_read_fd, pid_t pid);
void							first_argv_in_tab(t_data *data, char *input,
									char **env);
void							execute_with_slash(char *cmd, char **argv,
									char **envp);
void							handle_command_not_found(char **split_cmd);
void							handle_sigint_heredoc(int sig);
void							end_exe_heredoc(t_data *data, int fd,
									int *prev);
void							if_current_total(t_data *data, int current);
void							stock_here_end(int outfilefd, char *line);
void							free_line_current_plus(char **line,
									int *current);
void							current_total_cmp(int current, int total,
									t_data *data);
int								check_nbr_limiter(t_data *data);
void							int_var_stock(int *current, int *total,
									t_data *data);
void							run_heredoc_child(t_data *data);
int								builtin_heredoc(t_data *data);
int								wait_and_handle_heredoc(t_data *data,
									pid_t pid);
void							init_expans_var(char **temp, int *i,
									int *in_single_quotes, char **result);
int								check_double_pipe(t_data *data);
int								count_pipeline(t_data *data);
void							init_two_int(int *i, char *j);
void							two_int_init(int *i, int *j);
void							alloc_str_for_ex(t_data *data, char *str);
void							free_fds_and_pipelines(t_data *data);
int								bult_echo(t_data *data);
int								detect_bad_input(char **argv);
char							*handle_dollar_sign(char *str, int *i,
									char *result, t_data *data);
char							*copy_variable(int *i, char *result, char *temp,
									t_data *data);
char							*space_or_null_after_sign(char *temp,
									char *result);
void							print_cd_error(char *target);
void							handle_eacces_or_isdir(char *cmd_path);
int								is_redirection_operator(char *av);
int								is_redirection_operator2(char *token);
void							handle_command_not_found2(char **split_cmd,
									char *cmd_path);
void							close_pipe_if_needed(int *pipefd);

#endif