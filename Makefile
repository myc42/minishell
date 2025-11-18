# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/16 23:14:47 by macoulib          #+#    #+#              #
#    Updated: 2025/11/16 23:15:08 by macoulib         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = minishell

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3
INCLUDES    = -Iincludes

LIBFT_DIR   = librairie
LIBFT       = $(LIBFT_DIR)/libft.a

LDFLAGS     = -L$(LIBFT_DIR)
LDLIBS      = -lft -lreadline -lncurses -ltinfo

OBJ_DIR     = obj

SRCS = \
	src/ft_free/free_all.c \
	src/ft_free/free_tab.c \
	src/here_doc/exe_here_doc_utils.c \
	src/here_doc/here_doc_utils.c \
	src/here_doc/here_doc.c \
	src/here_doc/here_doc_utils2.c \
	src/here_doc/expansion_here_doc.c \
	src/here_doc/here_doc_utils4.c \
	src/here_doc/exe_here_doc.c \
	src/here_doc/here_doc_utils3.c \
	src/parsing/delete_multiple_space.c \
	src/parsing/z_parsing.c \
	src/parsing/separate_quotes.c \
	src/parsing/argv_valid_tab.c \
	src/parsing/clean_space.c \
	src/parsing/argv_valid_count.c \
	src/parsing/quotes_management.c \
	src/parsing/clean_quotes.c \
	src/parsing/search_expansion_replacement.c \
	src/parsing/expand_variables_in_string.c \
	src/parsing/other_error.c \
	src/parsing/search_path.c \
	src/execution/exe_utils2.c \
	src/execution/grep_.c \
	src/execution/z_execution.c \
	src/execution/exe_utils.c \
	src/execution/exe_utils3.c \
	src/execution/exe_utilis1.c \
	src/bultin/biltin.c \
	src/bultin/exe_echo_.c \
	src/bultin/utilis2.c \
	src/bultin/split_echo_segment.c \
	src/bultin/env.c \
	src/bultin/exe_echo.c \
	src/bultin/ex2.c \
	src/bultin/shell.c \
	src/bultin/biltin2.c \
	src/bultin/utilis.c \
	src/bultin/builtin_exit.c \
	src/bultin/echo_utils.c \
	src/bultin/ex.c \
	src/bultin/prompt.c \
	src/signaux/signal.c \
	src/redirection/file_in_out.c \
	src/redirection/pipeline_management.c \
	src/redirection/z_redirection.c \
	src/redirection/cmd_tab.c \
	src/redirection/pipe.c \
	src/redirection/utils_redirection.c \
	src/minishell.c

OBJS = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
