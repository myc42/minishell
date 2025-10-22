# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/22 18:56:36 by macoulib          #+#    #+#              #
#    Updated: 2025/10/22 18:14:07 by macoulib         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS      =   -g3 -O0 -Wall -Wextra -Werror -Iincludes
DEBUGFLAGS  =   -g3 -O0 -Wall -Wextra -Werror -fsanitize=address -fsanitize=undefined -fsanitize=leak -Iincludes

LDFLAGS     =   -lreadline -L$(LIBFT_DIR)
AR          =   ar rcs
RM          =   rm -f

NAME        =   minishell

# --- Chemins des sources ---
SRC_DIR     =   ./src
SRC_MAIN    =   $(SRC_DIR)/minishell.c
SRC_SUBDIRS =   parsing redirection utils execution bultin signaux here_doc ft_free

# Récupère tous les fichiers .c des sous-dossiers (e.g., parsing/file.c)
SRC_SUB = $(foreach dir, $(SRC_SUBDIRS), $(wildcard $(SRC_DIR)/$(dir)/*.c))

# Fichiers .c directement dans src/, en excluant minishell.c
SRC_TOP_LEVEL = $(filter-out $(SRC_MAIN), $(wildcard $(SRC_DIR)/*.c))

# Combine tous les fichiers .c sources
SRC         =   $(SRC_MAIN) $(SRC_TOP_LEVEL) $(SRC_SUB)

LIBFT_DIR   =   ./librairie/ft_libft
LIBFT_SRC   =   $(wildcard $(LIBFT_DIR)/*.c)

# --- Dépendances et Objets ---
OBJ_DIR     =   ./obj
INCLUDES    =   ./includes/minishell.h
HEADER_DEPS =   $(INCLUDES) $(LIBFT_DIR)/libft.h

# Calcule les noms des fichiers objets (ex: minishell.c -> obj/minishell.o)
# Notez l'utilisation de $(notdir ...) pour n'avoir que le nom du fichier.
OBJ_SRC     =   $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))
LIBFT_OBJ   =   $(addprefix $(OBJ_DIR)/, $(notdir $(LIBFT_SRC:.c=.o)))

# Tous les objets nécessaires à l'édition de liens
OBJ         =   $(OBJ_SRC) $(LIBFT_OBJ)

# Color codes (inchangés)
GREEN       =   \033[0;32m
YELLOW      =   \033[0;33m
CYAN        =   \033[0;36m
NC          =   \033[0m

# Target principal
all: $(NAME)

# --- Règles de compilation ---

# Règle pour créer le répertoire des objets
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Création de l'exécutable
$(NAME): $(OBJ_DIR) $(LIBFT_DIR)/libft.a $(OBJ)
	@echo "$(GREEN)Building $(NC)$(NAME)"
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

# Création de la librairie libft (règle inchangée)
$(LIBFT_DIR)/libft.a: $(LIBFT_OBJ)
	@echo "$(BLUE)Archiving $(NC)$@"
	$(AR) $@ $(LIBFT_OBJ)

# Règle générique pour la compilation de TOUS les fichiers .c
# 1. Utilise 'vpath' pour trouver les sources dans 'src' et ses sous-dossiers.
# 2. Utilise '%' pour générer l'objet (ex: obj/file.o) à partir de la source trouvée.
# NOUVELLE LIGNE CORRIGÉE
vpath %.c $(LIBFT_DIR) $(SRC_DIR) $(foreach dir, $(SRC_SUBDIRS), $(SRC_DIR)/$(dir))

$(OBJ_DIR)/%.o: %.c $(HEADER_DEPS)
	@echo "$(CYAN)Compiling $(NC)$<"
	$(CC) $(CFLAGS) -c $< -o $@

# --- Règles de nettoyage ---

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@echo "$(CYAN)Cleaning object files"
	$(RM) $(OBJ)
	@rmdir $(OBJ_DIR) 2>/dev/null || true

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(CYAN)Cleaning $(NC)$(NAME)"
	$(RM) $(NAME)

# --- Targets Spéciaux ---

re: fclean all

debug: $(OBJ_DIR) $(LIBFT_DIR)/libft.a $(OBJ)
	@echo "$(YELLOW)Building $(NC)$(NAME) $(YELLOW)with debug flags"
	$(CC) $(DEBUGFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

valgrind: $(NAME)
	@echo "$(YELLOW)🔍 Launching Valgrind on ./minishell...$(NC)"
	@valgrind -q --suppressions=./ignore --trace-children=yes \
		--leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes \
		./minishell

.PHONY: all clean fclean re debug valgrind