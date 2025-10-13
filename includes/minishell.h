/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 19:02:12 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/13 18:52:08 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../librairie/ft_libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data
{
	char	**envp;
	char	**argv;
	char	**argv_only_cmd;
	char	***argv_pipeline;
	int		infile_fd;
	int		outfile_fd;
	int		error_fd;
}			t_data;

int			ft_isspace(char c);
int			closed_quotes(char *str);
char		*expand_variables_in_string(char *str, char **envp);
char		*find_path(char **env, char *cmd);
char		*delete_multiple_space(char *str);
int			ft_strncmps(const char *s1, const char *s2, size_t n);
char		*search_expansion_replacement(char *str, char **envp);
char		*expand_variables_in_string(char *str, char **envp);
int			count_argv(char *str);
void		init_variable(int *argv, int *i, int *count, int *s, int *d);
void		is_word(int *argv, int *count, int s, int d);
char		**argv_valid_tab(char *str);
int			ft_strcmp(char *s1, char *s2);
int			ft_parsing(char *str, t_data *data, char **envp);
int			creat_fd_infile(t_data *data, int *i);
int			creat_fd_outfile(t_data *data, int *i);
int			is_redirection_operator(char *av);
int			redirect_and_cmds(t_data *data, int ac, char **envp);
int			count_cmd_elements(t_data *data);
int			only_cmd_tab(t_data *data);
int			direction_error(char *str, t_data *data);
int			fd_and_cmd_tab(t_data *data, char **av, int ac, char **envp);
int			redirection_detected(char **av);
void		create_pipeline_tab(t_data *data);
void		exe(t_data *data, char *input, int ac, char **env);
int			count_pipeline(t_data *data);
void		pipeline_space(char *str, char *dest);
void		init_variables_to_zero(int *i, int *j, int *k, int *l);
char		*clean_space(char *str);

#endif
